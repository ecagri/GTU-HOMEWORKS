DELIMITER //
DROP PROCEDURE IF EXISTS getMedicalRecords;
CREATE PROCEDURE getMedicalRecords(IN p_TC_in INTEGER)
BEGIN
    SELECT * 
    FROM MedicalRecords 
    WHERE p_TC_in = p_TC;
END; //
DELIMITER ;

CALL getMedicalRECORDS(1001);


DELIMITER //
DROP PROCEDURE IF EXISTS numberOfUniquePatientsSurgery;
CREATE PROCEDURE numberOfUniquePatientsSurgery()
BEGIN
    DECLARE counter INTEGER DEFAULT 0;
    DECLARE number_of_surgeries INTEGER DEFAULT 0;
    DECLARE number_of_uniquePatients INTEGER DEFAULT 0;
    DECLARE p_TC VARCHAR(50);
    DECLARE fullname VARCHAR(100);
    DECLARE birthdate DATE;
    DECLARE gender CHAR(1);
    DECLARE phone VARCHAR(20);

    CREATE TEMPORARY TABLE IF NOT EXISTS uniquePatients(
        TC VARCHAR(50),
        fullname VARCHAR(100),
        birthdate DATE,
        gender CHAR(1),
        phone VARCHAR(20)
    );

    SELECT COUNT(*) INTO number_of_surgeries FROM Surgeries;

    WHILE counter < number_of_surgeries DO
        SELECT p_TC, fullname, birthdate, gender, phone
        INTO p_TC, fullname, birthdate, gender, phone
        FROM Surgeries
        LIMIT counter, 1;

        IF NOT EXISTS (SELECT 1 FROM uniquePatients WHERE TC = p_TC) THEN
            INSERT INTO uniquePatients (TC, fullname, birthdate, gender, phone)
            VALUES (p_TC, fullname, birthdate, gender, phone);
        END IF;

        SET counter = counter + 1;
    END WHILE;

    SELECT COUNT(*) INTO number_of_uniquePatients FROM uniquePatients;

    SELECT number_of_uniquePatients AS NumberOfUniquePatients;
END; //
DELIMITER ;

CALL numberOfUniquePatientsSurgery;

DROP FUNCTION IF EXISTS patientSurgeryAppointmentRate;
DELIMITER //
CREATE FUNCTION patientSurgeryAppointmentRate(p_TC INTEGER)
RETURNS DECIMAL(10,2)
READS SQL DATA
DETERMINISTIC
BEGIN
    DECLARE number_of_medical_records INTEGER DEFAULT 0;
    DECLARE number_of_surgeries INTEGER DEFAULT 0;
    DECLARE surgeryAppointmentRate DECIMAL(10,2);

    SELECT COUNT(*) INTO number_of_medical_records FROM MedicalRecords WHERE MedicalRecords.p_TC = p_TC;
    SELECT COUNT(*) INTO number_of_surgeries FROM surgeries WHERE surgeries.p_TC = p_TC;

    IF number_of_medical_records > 0 THEN
        SET surgeryAppointmentRate = number_of_surgeries / number_of_medical_records;
    ELSE
        SET surgeryAppointmentRate = 0;
    END IF;

    RETURN surgeryAppointmentRate;
END; //
DELIMITER ;

SELECT p_TC, patientSurgeryAppointmentRate(p_TC) FROM patients;


DROP TRIGGER IF EXISTS postponeTrigger;
DELIMITER //
CREATE TRIGGER postponeTrigger
BEFORE UPDATE ON Appointments
FOR EACH ROW
BEGIN
    IF old.date > new.date THEN
        SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'Cannot update appointment to a date in the past';
    END IF;
END; //
DELIMITER ;

UPDATE Appointments SET date = date + INTERVAL 3 DAY WHERE a_id = 3001;
UPDATE Appointments SET date = date - INTERVAL 3 DAY WHERE a_id = 3001;


DROP TRIGGER IF EXISTS insertAppointmentAfterSurgery;
DELIMITER //
CREATE TRIGGER insertAppointmentAfterSurgery
AFTER INSERT ON Surgeries
FOR EACH ROW
BEGIN   
    DECLARE last_id INT;

    SELECT MAX(a_id) INTO last_id FROM Appointments;

    IF last_id IS NULL THEN
        SET last_id = 0;
    END IF;

    INSERT INTO Appointments (a_id, p_TC, d_id, date, time, reason)
    VALUES (last_id + 1, NEW.p_TC, NEW.d_id, NEW.date + INTERVAL 15 DAY, '09:00:00', 'Surgery Control');
END; //
DELIMITER ;

INSERT INTO Surgeries VALUES(5014, 1002, 2010, 'Leg Operation',  '2024-10-02');
Select Surgeries.p_TC, Surgeries.d_id, Surgeries.date as SurgeryDate, Appointments.date as AppointmentDate FROM Surgeries, Appointments
    WHERE Surgeries.p_TC = Appointments.p_TC and Surgeries.p_TC = 1002 and Surgeries.d_id = Appointments.d_id;


DROP TRIGGER IF EXISTS insertSurgery;
DELIMITER //
CREATE TRIGGER insertSurgery
BEFORE INSERT ON Surgeries
FOR EACH ROW
BEGIN
    DECLARE patient_age INT DEFAULT 0;
    SELECT age INTO patient_age from patients where patients.p_TC = new.p_TC;
    IF patient_age > 75 THEN
       DELETE FROM Appointments WHERE Appointments.date = new.date and new.p_TC != Appointments.p_TC; 
    END IF;
END; //
DELIMITER ;


INSERT INTO Surgeries VALUES(5015, 1010, 2002, 'Brain Surgery', '2024-06-15');
SELECT * FROM Appointments;


DELIMITER //
START TRANSACTION;

SET @best_doctor_id := NULL;

SELECT d_id INTO @best_doctor_id
FROM (
    SELECT d_id, COUNT(*) as count
    FROM appointments
    GROUP BY d_id
    ORDER BY count DESC
    LIMIT 1
) AS counts;

UPDATE doctors 
SET salary = CASE WHEN @best_doctor_id IS NOT NULL THEN salary * 2 ELSE salary END
WHERE d_id = @best_doctor_id;
COMMIT; //

DELIMITER ;

SELECT * FROM Doctors;

DELIMITER //
START TRANSACTION;
SET @last_id := NULL;
SELECT MAX(a_id) INTO @last_id FROM Appointments;
INSERT INTO Appointments (a_id, p_TC, d_id, date, time, reason)
VALUES (@last_id + 1, 1003, 2004, '2024-06-10', '12:00:00', 'Follow-up Check-up');

UPDATE MedicalRecords
SET diagnosis = 'Improved Arthritis Condition', treatment = 'Continued Physical Therapy'
WHERE p_TC = 1003;


COMMIT; // 

DELIMITER ;

SELECT * FROM MedicalRecords;