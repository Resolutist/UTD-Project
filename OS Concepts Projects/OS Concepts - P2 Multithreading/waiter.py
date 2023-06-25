import threading
import random
import time

class Waiter(threading.Thread):
    table_semaphores = {'A': threading.Semaphore(1), 'B': threading.Semaphore(1), 'C': threading.Semaphore(1)}
    order_semaphores = {'A': threading.Semaphore(0), 'B': threading.Semaphore(0), 'C': threading.Semaphore(0)}
    customer_order = {'A': None, 'B': None, 'C': None}

    def __init__(self, waiter_id, table_type):
        super(Waiter, self).__init__()
        self.waiter_id = waiter_id
        self.table_type = table_type

    def run(self):
        print(f'Waiter {self.waiter_id} is assigned to table {self.table_type}')

        while True:
            self.table_semaphores[self.table_type].acquire()

            if self.customer_order[self.table_type] is not None:
                print(f'Waiter {self.waiter_id} goes to table {self.table_type}')
                print(f'Waiter {self.waiter_id} takes Customer {self.customer_order[self.table_type]}\'s order')
                self.order_semaphores[self.table_type].release()

                print(f'Waiter {self.waiter_id} goes to the kitchen to deliver Customer {self.customer_order[self.table_type]}\'s order')
                time_spent_in_kitchen = random.randint(5, 30) / 1000
                time.sleep(time_spent_in_kitchen)
                print(f'Waiter {self.waiter_id} exits the kitchen and waits')

                self.order_semaphores[self.table_type].acquire()
                print(f'Waiter {self.waiter_id} enters the kitchen to pickup Customer {self.customer_order[self.table_type]}\'s food')
                time_spent_picking_up_food = random.randint(100, 500) / 1000
                time.sleep(time_spent_picking_up_food)
                print(f'Waiter {self.waiter_id} exits the kitchen')

                print(f'Waiter {self.waiter_id} brings food to Customer {self.customer_order[self.table_type]}')
                self.customer_order[self.table_type] = None
                self.table_semaphores[self.table_type].release()
            else:
                self.table_semaphores[self.table_type].release()
                time.sleep(0.1)
                continue

            if all([value is None for value in self.customer_order.values()]):
                print(f'Waiter {self.waiter_id} cleans the table at {self.table_type}')
                break

class Customer(threading.Thread):
    line_semaphores = {'A': threading.Semaphore(1), 'B': threading.Semaphore(1), 'C': threading.Semaphore(1)}
    table_semaphores = {'A': threading.Semaphore(4), 'B': threading.Semaphore(4), 'C': threading.Semaphore(4)}
    counter_semaphore = threading.Semaphore(1)
    line_counts = {'A': 0, 'B': 0, 'C': 0}
    table_counts = {'A': 0, 'B': 0, 'C': 0}
    table_customers = {'A': [], 'B': [], 'C': []}
    waiter_assignments = {'A': None, 'B': None, 'C': None}
    backup_tables = {'A': ['B', 'C'], 'B': ['A', 'C'], 'C': ['A', 'B']}

    def __init__(self, customer_id, preferred_table):
        super(Customer, self).__init__()
        self.customer_id = customer_id
        self.preferred_table = preferred_table
        self.backup_table = None
        self.chosen_table = None
        self.waiter_id = None

    def run(self):
        self.choose_table()
        self.enter_restaurant()
        self.get_in_line()
        self.wait_to_be_seated()

    def choose_table(self):
        self.backup_table = random.choice(self.backup_tables[self.preferred_table])
e
        self.counter_semaphore.acquire()

        if self.line_counts[self.preferred_table] < self.line_counts[self.backup_table] + 7:
            self.chosen_table = self.preferred_table
            self.line_counts[self.preferred_table] += 1
        else:
            self.chosen_table = self.backup_table
            self.line_counts[self.backup_table] += 1

        self.counter_semaphore.release()

        print(f'Customer {self.customer_id} wants to eat {self.preferred_table}')
        time.sleep(random.random())

    def enter_restaurant(self):
        door = random.randint(0, 1)
        if door == 0:
            print(f'Customer {self.customer_id} enters the restaurant through door 1')
        else:
            print(f'Customer {self.customer_id} enters the restaurant through door 2')
        time.sleep(random.random())

    def get_in_line(self):
        self.line_semaphores[self.chosen_table].acquire()

        print(f'Customer {self.customer_id} stands in line for table {self.chosen_table}')
        time.sleep(random.random())

    def wait_to_be_seated(self):
        self.table_semaphores[self.chosen_table].acquire()

        self.line_semaphores[self.chosen_table].release()

        self.table_counts[self.chosen_table] += 1
        self.table_customers[self.chosen_table].append(self.customer_id)

        if self.table_counts[self.chosen_table] > 4:
            print(f'Customer {self.customer_id} waits to be seated at table {self.chosen_table} with other customers {self.table_customers[self.chosen_table]}')
        else:
            print(f'Customer {self.customer_id} is seated at table {self.chosen_table}')
            time.sleep(random.random())

        def call_waiter(self):
            self.waiter_id = self.table_customers[self.chosen_table][0]

            self.waiter_assignments[self.chosen_table] = self.waiter_id

            print(f'Customer {self.customer_id} calls waiter {self.waiter_id}')

            time.sleep(random.random())

        def place_order(self):
            print(f'Customer {self.customer_id} places order with waiter {self.waiter_id}')
            time.sleep(random.random())

        def wait_for_food(self):
            print(f'Customer {self.customer_id} waits for food from waiter {self.waiter_id}')
            time.sleep(random.random())

        def eat_food(self):
            print(f'Customer {self.customer_id} eats food')
            time.sleep(random.random())

        def leave_table(self):
            self.table_counts[self.chosen_table] -= 1
            self.table_customers[self.chosen_table].remove(self.customer_id)

            self.table_semaphores[self.chosen_table].release()

            print(f'Customer {self.customer_id} leaves table {self.chosen_table}')
            time.sleep(random.random())

        def pay_for_meal(self):
            print(f'Customer {self.customer_id} pays for meal')
            time.sleep(random.random())

        def leave_restaurant(self):
            door = random.randint(0, 1)
            if door == 0:
                print(f'Customer {self.customer_id} leaves the restaurant through door 1')
            else:
                print(f'Customer {self.customer_id} leaves the restaurant through door 2')
            time.sleep(random.random())
