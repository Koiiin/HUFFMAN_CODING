import random
import string

def print_random_string(length):
    # Define the set of characters to choose from
    characters = string.ascii_letters + string.digits
    
    # Generate the random string
    random_string = ''.join(random.choice(characters) for _ in range(length))
    
    return random_string
# Example usage:
# random_str = random_string(1000)
# print(f"Random string: {random_str}")

HEAD = "DATA_INPUT_"
TAIL = ".txt"



for i in range(1,11):
    MID = str(i)
    file = HEAD + MID + TAIL;
    
    Password = print_random_string(1000)
    
    with open(file, "w") as f:
        f.write(f"{Password}")