DROP TABLE department, employee, customer, product, orders, orderDetail, shipment;
CREATE TABLE department(
  d_id INT PRIMARY KEY,
  d_name VARCHAR(50) NOT NULL,
  manager INT
);

CREATE TABLE employee (
  e_id INT PRIMARY KEY,
  e_name VARCHAR(50) NOT NULL,
  salary DECIMAL(10, 2),
  hire_date DATE,
  d_id INT REFERENCES department(d_id),
  CHECK (salary > 0)
);

CREATE TABLE customer (
  c_id INT PRIMARY KEY,
  c_name VARCHAR(50) NOT NULL,
  email VARCHAR(100),
  phone_number VARCHAR(20),
  balance INT,
  address varchar(100)
);

CREATE TABLE orders (
  o_id INT PRIMARY KEY,
  c_id INT REFERENCES customer(c_id),
  o_date DATE
);

CREATE TABLE orderDetail (
  od_id INT PRIMARY KEY,
  o_id INT REFERENCES orders(o_id),
  p_id INT REFERENCES product(p_id),
  quantity INT
);

CREATE TABLE product (
  p_id INT PRIMARY KEY,
  p_name VARCHAR(100) NOT NULL,
  price DECIMAL(10, 2),
  stock_quantity INT,
  e_id INT REFERENCES employee(e_id),
  CHECK (stock_quantity > 0),
  CHECK (price > 0)
);

CREATE TABLE shipment (
  s_id INT PRIMARY KEY,
  o_id INT REFERENCES orders(o_id),
  s_date DATE,
  s_address VARCHAR(255)
);

-- Insert data into the employee table
INSERT INTO employee (e_id, e_name, salary, hire_date, d_id) VALUES
(1, 'John Doe', 60000.00, '2020-01-15', 3),
(2, 'Jane Smith', 65000.00, '2019-03-10', 2),
(3, 'Bob Johnson', 55000.00, '2021-07-01', 1);

-- Insert data into the department table
INSERT INTO department (d_id, d_name, manager) VALUES
(1, 'Sales', 1),
(2, 'Marketing', 2),
(3, 'Development', 3);

-- Insert data into the customer table
INSERT INTO customer (c_id, c_name, email, phone_number, balance, address) VALUES
(1, 'Alice Brown', 'alice@example.com', '123-456-7890', 100, '123 Main St, Anytown, USA'),
(2, 'Charlie Green', 'charlie@example.com', '987-654-3210', 200, '456 Oak St, Othertown, USA');

-- Insert data into the orders table
INSERT INTO orders (o_id, c_id, o_date) VALUES
(1, 1, '2023-05-01'),
(2, 2, '2023-05-02');

-- Insert data into the product table
INSERT INTO product (p_id, p_name, price, stock_quantity, e_id) VALUES
(1, 'Product A', 10.50, 100, 1),
(2, 'Product B', 20.75, 200, 2);

-- Insert data into the orderDetail table
INSERT INTO orderDetail (od_id, o_id, p_id, quantity) VALUES
(1, 1, 1, 2),
(2, 2, 2, 3);

-- Insert data into the shipment table
INSERT INTO shipment (s_id, o_id, s_date, s_address) VALUES
(1, 1, '2023-05-03', '123 Main St, Anytown, USA'),
(2, 2, '2023-05-04', '456 Oak St, Othertown, USA');

