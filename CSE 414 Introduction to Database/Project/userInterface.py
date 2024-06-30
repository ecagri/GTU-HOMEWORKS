import tkinter as tk
from tkinter import messagebox, ttk
import mysql.connector

authenticated = False
role = None
password = None
def get_db_connection(role, password):
    connection = mysql.connector.connect(
        host="127.0.0.1",
        user=role,
        password=password,  
        database="databaseproject"
        )
    return connection

def execute_query(query, fetch=False):
    try:
        connection = get_db_connection(role, password)
        cursor = connection.cursor()
        cursor.execute(query)
        if fetch:
            result = cursor.fetchall()
            field_names = [i[0] for i in cursor.description]
            cursor.close()
            connection.close()
            return result, field_names
        else:
            connection.commit()
            cursor.close()
            connection.close()
            return None
    except mysql.connector.Error as err:
        messagebox.showerror("Error", f"Error: {err}")

def display_data(view):
    query = f"SELECT * FROM {view}"
    rows, field_names = execute_query(query, fetch=True)
    
    top = tk.Toplevel(root)
    top.title(view)

    if rows:
        for jdx, field_name in enumerate(field_names):
            header = tk.Label(top, text=field_name, borderwidth=1, relief="solid", font=('Arial', 10, 'bold'))
            header.grid(row=0, column=jdx, sticky="nsew")

        for idx, row in enumerate(rows):
            for jdx, col in enumerate(row):
                label = tk.Label(top, text=col, borderwidth=1, relief="solid")
                label.grid(row=idx+1, column=jdx, sticky="nsew")
    else:
        label = tk.Label(top, text="No data available", borderwidth=1, relief="solid")
        label.grid(row=0, column=0)


def login():
    global role, authenticated, password
    role = role_var.get()
    password = password_entry.get()
    if get_db_connection(role, password):
        authenticated = True
        login_window.destroy()  
        create_main_window()
    else:
        messagebox.showerror("Login Failed", "Invalid credentials")
def viewJoin(join_type):
    top = tk.Toplevel(root)
    top.title(f"View {join_type.capitalize()} Join")
    
    options = ['employee', 'customer', 'department', 'product', 'orders', 'orderDetail', 'Shipment']
    
    def create_dropdown(parent, row, column, options, command=None):
        var = tk.StringVar(parent)
        if len(options) > 0:
            var.set(options[0])
            dropdown = tk.OptionMenu(parent, var, *options, command=command)
            dropdown.grid(row=row, column=column)
        else:
            var.set("No match")
        return var
    
    def update_where_dropdown(*args):
        global where_options
        table1_name = table1_var.get()
        table2_name = table2_var.get()
        
        query = f"SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_SCHEMA = 'databaseproject' AND TABLE_NAME = '{table1_name}';"
        table1_fields = execute_query(query, fetch=True)
        
        query = f"SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_SCHEMA = 'databaseproject' AND TABLE_NAME = '{table2_name}';"
        table2_fields = execute_query(query, fetch=True)
        
        where_options = intersection_list_comp(table1_fields[0], table2_fields[0])
        where_dropdown['menu'].delete(0, 'end')
        for option in where_options:
            where_dropdown['menu'].add_command(label=option, command=tk._setit(where_var, option))
        
        where_var.set(where_options[0])  
    
    def intersection_list_comp(arr1, arr2):
        return [value for value in arr1 if value in arr2]
    
    tk.Label(top, text="Table 1").grid(row=0, column=0)
    tk.Label(top, text="Table 2").grid(row=1, column=0)
    tk.Label(top, text="WHERE").grid(row=2, column=0)

    table1_var = create_dropdown(top, 0, 1, options, command=update_where_dropdown)
    table2_var = create_dropdown(top, 1, 1, options, command=update_where_dropdown)
    where_var = tk.StringVar(top)
    where_dropdown = tk.OptionMenu(top, where_var, "")
    where_dropdown.grid(row=2, column=1)
    
    update_where_dropdown()

    def join():
        column_name = where_options[0]
        if not column_name:
            messagebox.showerror("Error", "Please select a WHERE condition.")
            return
        
        query_type = {
            'right': 'RIGHT OUTER JOIN',
            'left': 'LEFT OUTER JOIN',
            'full': 'FULL OUTER JOIN'
        }.get(join_type, 'RIGHT OUTER JOIN') 
        
        query = f"SELECT * FROM `{table1_var.get()}` {query_type} `{table2_var.get()}` ON `{table1_var.get()}`.`{column_name[0]}` = `{table2_var.get()}`.`{column_name[0]}`;"
        rows, field_names = execute_query(query, fetch=True)
        
        result_window = tk.Toplevel(root)
        result_window.title(f"{join_type.capitalize()} Join Result: '{table1_var.get()}' and '{table2_var.get()}'")

        if rows:
            for jdx, field_name in enumerate(field_names):
                header = tk.Label(result_window, text=field_name, borderwidth=1, relief="solid", font=('Arial', 10, 'bold'))
                header.grid(row=0, column=jdx, sticky="nsew")

            for idx, row in enumerate(rows):
                for jdx, col in enumerate(row):
                    label = tk.Label(result_window, text=col, borderwidth=1, relief="solid")
                    label.grid(row=idx+1, column=jdx, sticky="nsew")
        else:
            label = tk.Label(result_window, text="No data available", borderwidth=1, relief="solid")
            label.grid(row=0, column=0)
        

    tk.Button(top, text=f"{join_type.capitalize()} Join", command=join).grid(row=3, column=1)



def create_main_window():
    global root
    root = tk.Tk()
    root.title("Database")

    tk.Button(root, text="Insert Employee", command=create_insert_employee_ui).grid(row=0, column=1)
    tk.Button(root, text="Insert Customer", command=create_insert_customer_ui).grid(row=1, column=1)
    tk.Button(root, text="Insert Department", command=create_insert_department_ui).grid(row=2, column=1)
    tk.Button(root, text="Insert Product", command=create_insert_product_ui).grid(row=3, column=1)
    tk.Button(root, text="Insert Order", command=create_insert_order_ui).grid(row=4, column=1)
    tk.Button(root, text="Insert Order Detail", command=create_insert_order_detail_ui).grid(row=5, column=1)
    tk.Button(root, text="Insert Shipment", command=create_insert_shipment_ui).grid(row=6, column=1)

    views = ['Employee', 'Customer','Department', 'Product', 'Orders', 'OrderDetail',  'Shipment', 'DetailedOrder', 'EmployeeSupervisor', 'PerformanceEvaluation', 'ShipmentEvaluation', 'ContactCustomer']
    for idx, view in enumerate(views):
        tk.Button(root, text=f"View {view}", command=lambda v=view: display_data(v)).grid(row=0 + idx, column=0)

    tk.Button(root, text="Right Join", command=lambda: viewJoin('right')).grid(row=12, column=0)
    tk.Button(root, text="Left Join", command=lambda: viewJoin('left')).grid(row=13, column=0)
    tk.Button(root, text="Full Outer Join", command=lambda: viewJoin('full')).grid(row=14, column=0)

    tables = {
        "employee": "e_id",
        "customer": "c_id",
        "department": "d_id",
        "product": "p_id",
        "orders": "o_id",
        "orderDetail": "od_id",
        "shipment": "s_id"
    }

    for idx, (table_name, primary_key) in enumerate(tables.items(), start=0):
        tk.Button(root, text=f"Delete {table_name.capitalize()}",
                  command=lambda t=table_name, pk=primary_key: create_delete_record_ui(t, pk)).grid(row=0 + idx, column=3)

    tk.Button(root, text="Update Employee", 
              command=lambda: create_update_record_ui("employee", "e_id", ["e_name", "salary", "hire_date", "d_id"])).grid(row=0, column=4)

    tk.Button(root, text="Update Customer", 
              command=lambda: create_update_record_ui("customer", "c_id", ["c_name", "email", "phone_number", "balance", "address"])).grid(row=1, column=4)

    tk.Button(root, text="Update Department", 
              command=lambda: create_update_record_ui("department", "d_id", ["d_name", "manager"])).grid(row=2, column=4)

    tk.Button(root, text="Update Product", 
              command=lambda: create_update_record_ui("product", "p_id", ["p_name", "price", "stock_quantity", "e_id"])).grid(row=3, column=4)

    tk.Button(root, text="Update Orders", 
              command=lambda: create_update_record_ui("orders", "o_id", ["c_id", "o_date"])).grid(row=4, column=4)

    tk.Button(root, text="Update Order Detail", 
              command=lambda: create_update_record_ui("orderDetail", "od_id", ["o_id", "p_id", "quantity"])).grid(row=5, column=4)

    tk.Button(root, text="Update Shipment", 
              command=lambda: create_update_record_ui("shipment", "s_id", ["o_id", "s_date", "s_address"])).grid(row=6, column=4)

    root.mainloop()

def create_insert_employee_ui():
    top = tk.Toplevel(root)
    top.title("Insert Employee")

    tk.Label(top, text="Employee Name").grid(row=0, column=0)
    tk.Label(top, text="Salary").grid(row=1, column=0)
    tk.Label(top, text="Hire Date").grid(row=2, column=0)
    tk.Label(top, text="Department ID").grid(row=3, column=0)

    employee_name = tk.Entry(top)
    salary = tk.Entry(top)
    hire_date = tk.Entry(top)
    department_id = tk.Entry(top)

    employee_name.grid(row=0, column=1)
    salary.grid(row=1, column=1)
    hire_date.grid(row=2, column=1)
    department_id.grid(row=3, column=1)

    def insert_employee():
        query = "SELECT MAX(e_id) FROM employee"
        result = execute_query(query, fetch=True)
        max_od_id = result[0] if result and result[0] else 0
        e_id = max_od_id[0][0] + 1
        name = employee_name.get()
        sal = salary.get()
        hire = hire_date.get()
        dept_id = department_id.get()
        query = f"INSERT INTO employee (e_id, e_name, salary, hire_date, d_id) VALUES ({e_id}, '{name}', {sal}, '{hire}', {dept_id})"
        execute_query(query)
        messagebox.showinfo("Success", "Employee Inserted Successfully")

    tk.Button(top, text="Insert", command=insert_employee).grid(row=4, column=1)

def create_insert_customer_ui():
    top = tk.Toplevel(root)
    top.title("Insert Customer")

    tk.Label(top, text="Customer Name").grid(row=0, column=0)
    tk.Label(top, text="Email").grid(row=1, column=0)
    tk.Label(top, text="Phone Number").grid(row=2, column=0)
    tk.Label(top, text="Balance").grid(row=3, column=0)

    customer_name = tk.Entry(top)
    email = tk.Entry(top)
    phone_number = tk.Entry(top)
    balance = tk.Entry(top)

    customer_name.grid(row=0, column=1)
    email.grid(row=1, column=1)
    phone_number.grid(row=2, column=1)
    balance.grid(row=3, column=1)

    def insert_customer():
        query = "SELECT MAX(c_id) FROM customer"
        result = execute_query(query, fetch=True)
        max_od_id = result[0] if result and result[0] else 0
        c_id = max_od_id[0][0] + 1
        name = customer_name.get()
        email_val = email.get()
        phone = phone_number.get()
        bal = balance.get()
        query = f"INSERT INTO customer (c_id, c_name, email, phone_number, balance) VALUES ({c_id}, '{name}', '{email_val}', '{phone}', {bal})"
        execute_query(query)
        messagebox.showinfo("Success", "Customer Inserted Successfully")

    tk.Button(top, text="Insert", command=insert_customer).grid(row=4, column=1)

def create_insert_department_ui():
    top = tk.Toplevel(root)
    top.title("Insert Department")
    tk.Label(top, text="Department Name").grid(row=0, column=0)
    tk.Label(top, text="Manager").grid(row=1, column=0)

    department_name = tk.Entry(top)
    manager = tk.Entry(top)

    department_name.grid(row=0, column=1)
    manager.grid(row=1, column=1)

    def insert_department():
        query = "SELECT MAX(d_id) FROM department"
        result = execute_query(query, fetch=True)
        max_od_id = result[0] if result and result[0] else 0
        d_id = max_od_id[0][0] + 1
        name = department_name.get()
        mgr = manager.get()
        query = f"INSERT INTO department (d_id, d_name, manager) VALUES ({d_id}, '{name}', '{mgr}')"
        execute_query(query)
        messagebox.showinfo("Success", "Department Inserted Successfully")

    tk.Button(top, text="Insert", command=insert_department).grid(row=2, column=1)

def create_insert_product_ui():
    top = tk.Toplevel(root)
    top.title("Insert Product")

    tk.Label(top, text="Product Name").grid(row=0, column=0)
    tk.Label(top, text="Price").grid(row=1, column=0)
    tk.Label(top, text="Stock Quantity").grid(row=2, column=0)
    tk.Label(top, text="Employee ID").grid(row=3, column=0)

    product_name = tk.Entry(top)
    price = tk.Entry(top)
    stock_quantity = tk.Entry(top)
    employee_id = tk.Entry(top)

    product_name.grid(row=0, column=1)
    price.grid(row=1, column=1)
    stock_quantity.grid(row=2, column=1)
    employee_id.grid(row=3, column=1)

    def insert_product():
        query = "SELECT MAX(p_id) FROM product"
        result = execute_query(query, fetch=True)
        max_od_id = result[0] if result and result[0] else 0
        p_id = max_od_id[0][0] + 1
        name = product_name.get()
        prc = price.get()
        qty = stock_quantity.get()
        emp_id = employee_id.get()
        query = f"INSERT INTO product (p_id, p_name, price, stock_quantity, e_id) VALUES ({p_id}, '{name}', {prc}, {qty}, {emp_id})"
        execute_query(query)
        messagebox.showinfo("Success", "Product Inserted Successfully")

    tk.Button(top, text="Insert", command=insert_product).grid(row=4, column=1)

def create_insert_order_ui():
    top = tk.Toplevel(root)
    top.title("Insert Order")

    tk.Label(top, text="Customer ID").grid(row=0, column=0)
    tk.Label(top, text="Order Date").grid(row=1, column=0)

    customer_id = tk.Entry(top)
    order_date = tk.Entry(top)

    customer_id.grid(row=0, column=1)
    order_date.grid(row=1, column=1)

    def insert_order():
        query = "SELECT MAX(o_id) FROM orders"
        result = execute_query(query, fetch=True)
        max_od_id = result[0] if result and result[0] else 0
        o_id = max_od_id[0][0] + 1
        c_id = customer_id.get()
        odate = order_date.get()
        query = f"INSERT INTO orders (o_id, c_id, o_date) VALUES ({o_id}, {c_id}, '{odate}')"
        execute_query(query)
        messagebox.showinfo("Success", "Order Inserted Successfully")

    tk.Button(top, text="Insert", command=insert_order).grid(row=2, column=1)

def create_insert_order_detail_ui():
    top = tk.Toplevel(root)
    top.title("Insert Order Detail")

    tk.Label(top, text="Order ID").grid(row=0, column=0)
    tk.Label(top, text="Product ID").grid(row=1, column=0)
    tk.Label(top, text="Quantity").grid(row=2, column=0)

    order_id = tk.Entry(top)
    product_id = tk.Entry(top)
    quantity = tk.Entry(top)

    order_id.grid(row=0, column=1)
    product_id.grid(row=1, column=1)
    quantity.grid(row=2, column=1)

    def insert_order_detail():
        query = "SELECT MAX(od_id) FROM orderDetail"
        result = execute_query(query, fetch=True)
        max_od_id = result[0] if result and result[0] else 0
        od_id = max_od_id[0][0] + 1
        oid = order_id.get()
        pid = product_id.get()
        qty = quantity.get()
        query = f"INSERT INTO orderDetail (od_id, o_id, p_id, quantity) VALUES ({od_id}, {oid}, {pid}, {qty})"
        execute_query(query)
        messagebox.showinfo("Success", "Order Detail Inserted Successfully")

    tk.Button(top, text="Insert", command=insert_order_detail).grid(row=3, column=1)

def create_insert_shipment_ui():
    top = tk.Toplevel(root)
    top.title("Insert Shipment")

    tk.Label(top, text="Order ID").grid(row=0, column=0)
    tk.Label(top, text="Shipment Date").grid(row=1, column=0)
    tk.Label(top, text="Shipment Address").grid(row=2, column=0)

    order_id = tk.Entry(top)
    shipment_date = tk.Entry(top)
    shipment_address = tk.Entry(top)

    order_id.grid(row=0, column=1)
    shipment_date.grid(row=1, column=1)
    shipment_address.grid(row=2, column=1)

    def insert_shipment():
        query = "SELECT MAX(s_id) FROM shipment"
        result = execute_query(query, fetch=True)
        max_od_id = result[0] if result and result[0] else 0
        s_id = max_od_id[0][0] + 1
        oid = order_id.get()
        sdate = shipment_date.get()
        sadd = shipment_address.get()
        query = f"INSERT INTO shipment (s_id, o_id, s_date, s_address) VALUES ({s_id}, {oid}, '{sdate}', '{sadd}')"
        execute_query(query)
        messagebox.showinfo("Success", "Shipment Inserted Successfully")

    tk.Button(top, text="Insert", command=insert_shipment).grid(row=3, column=1)

def create_delete_record_ui(table, primary_key):
    top = tk.Toplevel(root)
    top.title(f"Delete {table.capitalize()}")

    tk.Label(top, text=f"Enter {primary_key} to delete").grid(row=0, column=0)
    entry = tk.Entry(top)
    entry.grid(row=0, column=1)

    def delete_record():
        pk_value = entry.get()
        query = f"DELETE FROM {table} WHERE {primary_key} = {pk_value}"
        execute_query(query)
        messagebox.showinfo("Success", f"{table.capitalize()} Record Deleted Successfully")

    tk.Button(top, text="Delete", command=delete_record).grid(row=1, column=1)

def create_update_record_ui(table, primary_key, fields):
    top = tk.Toplevel(root)
    top.title(f"Update {table.capitalize()}")

    tk.Label(top, text=f"Enter {primary_key} to update").grid(row=0, column=0)
    entry = tk.Entry(top)
    entry.grid(row=0, column=1)

    entry_values = []
    for idx, field in enumerate(fields):
        tk.Label(top, text=f"New {field.capitalize()}").grid(row=idx+1, column=0)
        entry_values.append(tk.Entry(top))
        entry_values[-1].grid(row=idx+1, column=1)

    def update_record():
        pk_value = entry.get()
        set_values = ", ".join([f"{fields[i]} = '{entry_values[i].get()}'" for i in range(len(fields)) if entry_values[i].get() != ""])
        query = f"UPDATE {table} SET {set_values} WHERE {primary_key} = {pk_value}"
        execute_query(query)
        messagebox.showinfo("Success", f"{table.capitalize()} Record Updated Successfully")

    tk.Button(top, text="Update", command=update_record).grid(row=len(fields)+1, column=1)

login_window = tk.Tk()
login_window.title("Login")

tk.Label(login_window, text="Role").grid(row=0, column=0)
tk.Label(login_window, text="Password").grid(row=1, column=0)

roles = ['çağrı', 'employee', 'user'] 
role_var = tk.StringVar(login_window)
role_dropdown = ttk.Combobox(login_window, textvariable=role_var, values=roles)
role_dropdown.grid(row=0, column=1)
role_dropdown.current(0)  

password_entry = tk.Entry(login_window, show="*")
password_entry.grid(row=1, column=1)

login_button = tk.Button(login_window, text="Login", command=login)
login_button.grid(row=2, columnspan=2)

login_window.mainloop()

