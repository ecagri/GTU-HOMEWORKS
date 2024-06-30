DROP TRIGGER IF EXISTS cancelOrder;
DELIMITER //
CREATE TRIGGER cancelOrder -- when an order is deleted from the system, the total price of the order will be refunded to the customer.
BEFORE DELETE ON orders
FOR EACH ROW
BEGIN
    DECLARE total_price DECIMAL(10,2);
    
    SELECT SUM(od.quantity * p.price) INTO total_price
    FROM orderDetail od
    INNER JOIN product p ON od.p_id = p.p_id
    WHERE od.o_id = OLD.o_id;

    UPDATE customer
    SET balance = balance + total_price
    WHERE c_id = OLD.c_id;
END; //
DELIMITER ;

DROP TRIGGER IF EXISTS addressChange;
DELIMITER //
CREATE TRIGGER addressChange -- Updates the shipment address if the customer's address is changed.
BEFORE UPDATE ON customer
FOR EACH ROW
BEGIN
	SET SQL_SAFE_UPDATES = 0;
    UPDATE shipment 
    SET shipment.s_address = NEW.address
    WHERE shipment.o_id IN (
        SELECT orders.o_id FROM orders WHERE orders.c_id = NEW.c_id and shipment.o_id = orders.o_id
    );
    SET SQL_SAFE_UPDATES = 1;
END; //
DELIMITER ;

DROP TRIGGER IF EXISTS updateStockQuantity;
DELIMITER // 
CREATE TRIGGER updateStockQuantity -- when an order is placed, the stock quantity of the corresponding product decreases.
BEFORE INSERT ON orderDetail 
FOR EACH ROW
BEGIN
    UPDATE product 
    SET stock_quantity = stock_quantity - NEW.quantity
    WHERE product.p_id = NEW.p_id;
END; //
DELIMITER ;

DROP TRIGGER IF EXISTS updatePrice;
DELIMITER // 
CREATE TRIGGER updatePrice -- increases the product price if its quantity decreases.
BEFORE UPDATE ON product 
FOR EACH ROW
BEGIN
	IF NEW.stock_quantity < OLD.stock_quantity THEN
		SET NEW.price = (OLD.price * OLD.stock_quantity) / (NEW.stock_quantity);
	END IF;
END; //
DELIMITER ;

DROP TRIGGER IF EXISTS createProduct;
DELIMITER // 
CREATE TRIGGER createProduct -- gives an employee a raise if they produce a product.
BEFORE INSERT ON product 
FOR EACH ROW
BEGIN
	UPDATE employee
    SET salary = salary * 1.025 
    WHERE NEW.e_id = employee.e_id;
END; //
DELIMITER ;

DROP VIEW IF EXISTS DetailedOrder;  
CREATE VIEW DetailedOrder AS -- gets the total price of an order.
SELECT orders.o_id, orders.c_id, orderDetail.quantity, product.price, orderDetail.quantity * product.price as total_amount
FROM orders, orderDetail, product
WHERE orders.o_id = orderDetail.o_id AND orderDetail.p_id = product.p_id;

-- SELECT * from DetailedOrder;

DROP VIEW IF EXISTS EmployeeSupervisor;
CREATE VIEW EmployeeSupervisor AS -- gets the name of the supervisor of the employee to complain about him.
SELECT e_id, e_name, manager as supervisor
FROM employee, department
WHERE employee.d_id = department.d_id;

-- SELECT * FROM EmployeeSupervisor;

DROP VIEW IF EXISTS PerformanceEvaluation; 
CREATE VIEW PerformanceEvaluation AS  -- evaluates employees in terms of their number of products.
SELECT e_id, COUNT(p_id) as product_number FROM product group by e_id;

-- SELECT * FROM PerformanceEvaluation;

DROP VIEW IF EXISTS ShipmentEvaluation;
CREATE VIEW ShipmentEvaluation AS -- evaluates shipment in terms of delivery date.
SELECT s_id, o_date, s_date, s_date - o_date as delivery_time
FROM shipment, orders
WHERE shipment.o_id = orders.o_id;

-- SELECT * FROM ShipmentEvaluation;

DROP VIEW IF EXISTS ContactCustomer; 
CREATE VIEW ContactCustomer AS -- if a product has problems, get the contact info of customer to inform him.
SELECT customer.c_id, customer.c_name, phone_number, product.p_id, product.p_name
FROM customer, product, orders, orderDetail
WHERE orders.c_id = customer.c_id and orderDetail.o_id = orders.o_id and product.p_id = orderDetail.p_id;


START TRANSACTION; -- decreases customer balance according to total amount of the order.
INSERT INTO orderDetail VALUES (9, 3, 1, 2);
SET @total_amount := NULL;
SELECT quantity * price INTO @total_amount FROM orderDetail, product WHERE orderDetail.od_id = 8 and orderDetail.p_id = product.p_id; 
UPDATE customer 
SET balance = balance - @total_amount
WHERE customer.c_id IN (
SELECT c_id FROM orders, orderDetail 
where orderDetail.od_id = 8 and orderDetail.o_id = orders.o_id);
COMMIT;

START TRANSACTION; -- gives an employee a raise if they have produced the most products.
SET @best_employee := NULL;
SELECT e_id INTO @best_employee FROM performanceevaluation ORDER BY product_number DESC LIMIT 1;
UPDATE employee
SET SALARY = SALARY * 1.025
WHERE e_id = @best_employee;
COMMIT;

START TRANSACTION; -- updates products' price.

UPDATE product SET price = price * 1.5 WHERE p_id = 2;

COMMIT;
 
DROP USER IF EXISTS 'user';
CREATE USER 'user' IDENTIFIED BY 'user';
GRANT SELECT ON databaseproject.product TO 'user';
GRANT UPDATE ON databaseproject.orderdetail TO 'user';

DROP USER IF EXISTS 'çağrı';
CREATE USER 'çağrı' IDENTIFIED BY 'çaycı';
GRANT ALL PRIVILEGES ON databaseproject.* TO 'çağrı';


DROP USER IF EXISTS 'employee';
CREATE USER 'employee' IDENTIFIED BY 'employee';
GRANT UPDATE, INSERT, DELETE, SELECT ON databaseproject.employee TO 'employee';
GRANT UPDATE, INSERT, DELETE, SELECT ON databaseproject.orderdetail TO 'employee';
GRANT UPDATE, INSERT, DELETE, SELECT ON databaseproject.orders TO 'employee';
GRANT UPDATE, INSERT, DELETE, SELECT ON databaseproject.product TO 'employee';
GRANT UPDATE, INSERT, DELETE, SELECT ON databaseproject.shipment TO 'employee';
FLUSH PRIVILEGES;
