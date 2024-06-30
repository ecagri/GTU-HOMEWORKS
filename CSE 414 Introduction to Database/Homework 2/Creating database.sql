CREATE TABLE Patients (
  p_TC INT PRIMARY KEY,
  fullname VARCHAR(255),
  birthdate DATE,
  gender CHAR(1),
  phone VARCHAR(20),
  age INT
);

CREATE TABLE Doctors (
  d_id INT PRIMARY KEY,
  fullname VARCHAR(255),
  birthdate DATE,
  gender CHAR(1),
  phone VARCHAR(20),
  department VARCHAR(255),
  salary INT
);

CREATE TABLE Appointments (
  a_id INT PRIMARY KEY,
  p_TC INT,
  d_id INT,
  date DATE,
  time TIME,
  reason VARCHAR(255),
  FOREIGN KEY (p_TC) REFERENCES Patients(p_TC),
  FOREIGN KEY (d_id) REFERENCES Doctors(d_id)
);

CREATE TABLE MedicalRecords (
  r_id INT PRIMARY KEY,
  p_TC INT,
  d_id INT,
  diagnosis VARCHAR(255),
  treatment VARCHAR(255),
  date DATE,
  FOREIGN KEY (p_TC) REFERENCES Patients(p_TC),
  FOREIGN KEY (d_id) REFERENCES Doctors(d_id)
);

CREATE TABLE Surgeries (
  s_id INT PRIMARY KEY,
  p_TC INT,
  d_id INT,
  type VARCHAR(255),
  date DATE,
  FOREIGN KEY (p_TC) REFERENCES Patients(p_TC),
  FOREIGN KEY (d_id) REFERENCES Doctors(d_id)
);

-- Patients table
INSERT INTO Patients (p_TC, fullname, birthdate, gender, phone, age) 
VALUES 
(1001, 'John Smith', '1990-05-15', 'M', '123-456-7890', 31),
(1002, 'Alice Johnson', '1985-08-20', 'F', '987-654-3210', 36),
(1003, 'Michael Brown', '1978-02-10', 'M', '555-555-5555', 43),
(1004, 'Emily Davis', '1995-10-25', 'F', '111-222-3333', 26),
(1005, 'David Martinez', '1980-12-01', 'M', '999-888-7777', 41),
(1006, 'Sarah Wilson', '1982-07-08', 'F', '444-333-2222', 39),
(1007, 'Robert Anderson', '1992-04-18', 'M', '666-777-8888', 29),
(1008, 'Jennifer Taylor', '1987-09-30', 'F', '333-222-1111', 34),
(1009, 'Daniel Rodriguez', '1975-03-12', 'M', '222-333-4444', 49),
(1010, 'Jessica Garcia', '1998-06-23', 'F', '777-888-9999', 26);

-- Doctors table
INSERT INTO Doctors (d_id, fullname, birthdate, gender, phone, department, salary) 
VALUES 
(2001, 'Dr. Michael Johnson', '1970-09-05', 'M', '111-111-1111', 'Cardiology', 120000),
(2002, 'Dr. Emily White', '1982-03-15', 'F', '222-222-2222', 'Pediatrics', 110000),
(2003, 'Dr. David Brown', '1975-11-20', 'M', '333-333-3333', 'Orthopedics', 125000),
(2004, 'Dr. Sarah Miller', '1988-07-10', 'F', '444-444-4444', 'Neurology', 130000),
(2005, 'Dr. James Lee', '1972-01-30', 'M', '555-555-5555', 'Oncology', 135000),
(2006, 'Dr. Anna Clark', '1980-05-18', 'F', '666-666-6666', 'Dermatology', 115000),
(2007, 'Dr. William Martinez', '1990-12-25', 'M', '777-777-7777', 'Urology', 125000),
(2008, 'Dr. Samantha Taylor', '1985-08-08', 'F', '888-888-8888', 'Gastroenterology', 130000),
(2009, 'Dr. Daniel Hernandez', '1977-04-01', 'M', '999-999-9999', 'ENT', 120000),
(2010, 'Dr. Jessica Adams', '1993-06-10', 'F', '000-000-0000', 'Psychiatry', 110000);

-- Appointments table
INSERT INTO Appointments (a_id, p_TC, d_id, date, time, reason) 
VALUES 
(3001, 1001, 2001, '2024-06-10', '09:00:00', 'Routine checkup'),
(3002, 1002, 2002, '2024-06-12', '10:30:00', 'Vaccination'),
(3003, 1003, 2003, '2024-06-15', '11:15:00', 'Fracture treatment'),
(3004, 1004, 2004, '2024-06-18', '14:00:00', 'Headache consultation'),
(3005, 1005, 2005, '2024-06-20', '15:30:00', 'Chemotherapy session'),
(3006, 1006, 2006, '2024-06-22', '16:45:00', 'Skin rash examination'),
(3007, 1007, 2007, '2024-06-25', '09:30:00', 'Prostate checkup'),
(3008, 1008, 2008, '2024-06-28', '13:00:00', 'Colonoscopy'),
(3009, 1009, 2009, '2024-06-30', '11:45:00', 'Ear infection treatment'),
(3010, 1010, 2010, '2024-07-02', '10:00:00', 'Therapy session');

-- MedicalRecords table
INSERT INTO MedicalRecords (r_id, p_TC, d_id, diagnosis, treatment, date) 
VALUES 
(4001, 1001, 2001, 'High blood pressure', 'Prescribed medication', '2024-06-10'),
(4002, 1002, 2002, 'Flu', 'Antiviral medication', '2024-06-12'),
(4003, 1003, 2003, 'Broken leg', 'Leg cast', '2024-06-15'),
(4004, 1004, 2004, 'Migraine', 'Painkillers', '2024-06-18'),
(4005, 1005, 2005, 'Stage 3 cancer', 'Chemotherapy', '2024-06-20'),
(4006, 1006, 2006, 'Contact dermatitis', 'Topical cream', '2024-06-22'),
(4007, 1007, 2007, 'Prostate enlargement', 'Prescribed medication', '2024-06-25'),
(4008, 1008, 2008, 'Polyp', 'Removed during colonoscopy', '2024-06-28'),
(4009, 1009, 2009, 'Ear infection', 'Antibiotics', '2024-06-30'),
(4010, 1010, 2010, 'Depression', 'Therapy sessions', '2024-07-02');

-- Surgeries table
INSERT INTO Surgeries (s_id, p_TC, d_id, type, date) 
VALUES 
(5001, 1003, 2003, 'Leg fracture repair', '2024-06-16'),
(5002, 1005, 2005, 'Tumor removal', '2024-06-21'),
(5003, 1006, 2006, 'Dermabrasion', '2024-06-23'),
(5004, 1007, 2007, 'Prostatectomy', '2024-06-26'),
(5008, 1008, 2008, 'Colon polypectomy', '2024-06-29'),
(5009, 1009, 2009, 'Tympanoplasty', '2024-07-01'),
(5010, 1010, 2010, 'None', '2024-08-15');
