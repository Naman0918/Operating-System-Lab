#!/bin/bash
#is to tell the system that this is a bash script
#Initialize a variable to keep track of the current highest ID
current_id=0

# Function to create a new address book file named "addressbook1.txt"
create() {
    touch addressbook1.txt # touch command is used to create a file
    echo "AddressBook Created Successfully"
    echo
}

# Function to get the next available ID
get_next_id() {
    # Generate a random number between 1 and 1000
    current_id=$((1 + RANDOM % 1000))
    echo "$current_id"
}

# Function to display the contents of the address book file
display() {
    cat addressbook1.txt # cat command is used to display the contents of a file
    echo
}

# Function to insert a new record into the address book file
insert() {
    id=$(get_next_id)
    while true; do
        echo "Enter name: "
        read name
        # Validate name does not contain special characters
        if [[ "$name" =~ [^a-zA-Z[:space:]] ]]; then
            echo "Invalid name. Name should only contain letters, numbers, and spaces."
        else
            break
        fi
    done

    while true; do
        echo "Enter phone: "
        read phone
        # Validate phone is numeric
        if ! [[ "$phone" =~ ^[0-9]{10}$ ]]; then # use of $ to get the value of the variable
            echo "Invalid phone number. Please enter a valid numeric value with 10 digits."
        else
            break
        fi
    done

    while true; do
        echo "Enter city: "
        read city
        # Validate city does not contain special characters
        if [[ "$city" =~ [^a-zA-Z0-9[:space:]] ]]; then
            echo "Invalid city. City should only contain letters, numbers, and spaces."
        else
            break
        fi
    done

    while true; do
        echo "Enter pincode: "
        read pincode
        # Validate pincode is numeric
        if ! [[ "$pincode" =~ ^[0-9]{6}$ ]]; then
            echo "Invalid pincode. Please enter a valid numeric value with 6 digits."
        else
            break
        fi
    done

    echo "$id $name $phone $city $pincode" >> addressbook1.txt # >> command is used to append the contents to a file
    echo "Insert Successfully"
    echo
}

# Function to delete a record from the address book file by ID
delete() {
    echo "Enter the id you want to delete: "
    read id
    # Check if the record with the specified ID exists
    if ! grep -q "^$id\s" addressbook1.txt; then # -q is used to suppress the output of grep command
        echo "Record with ID $id not found."
        return
    fi
    # Create a temporary file without the record to be deleted, then replace the original file
    grep -v "^$id\s" addressbook1.txt >temp.txt # grep command is used to search for a pattern in a file and -v is used to invert the match
    mv temp.txt addressbook1.txt # mv command is used to move a file 
    echo "Record Deleted Successfully"
    echo
}

# Function to modify a record in the address book file by ID
modify() {
    echo "Enter the ID you want to Modify: "
    read id
    # Check if the record with the specified ID exists
    if ! grep -q "^$id\s" addressbook1.txt; then
        echo "Record with ID $id not found."
        return
    fi
    echo "Enter new name: "
    read name
    echo "Enter new phone: "
    read phone
    echo "Enter new city: "
    read city
    echo "Enter new pincode: "
    read pincode
    # Use 'sed' command to replace the line containing the old record with the new record
    sed -i "/^$id\s/c$id $name $phone $city $pincode" addressbook1.txt

    echo "Modified Successfully"
    echo
}


# Function to display the menu options
menu() {
    echo "******"
    echo "* 1. Create  *"
    echo "* 2. Display *"
    echo "* 3. Insert  *"
    echo "* 4. Delete  *"
    echo "* 5. Modify  *"
    echo "* 6. Exit    *"
    echo "******"
}

# Infinite loop to keep the program running until the user chooses to exit
while true; do
    menu
    echo "Enter your choice: "
    read choice
    echo

    # Process the user's choice using a case statement
    case $choice in
    1) create ;;  # Call the create function
    2) display ;; # Call the display function
    3) insert ;;  # Call the insert function
    4) delete ;;  # Call the delete function
    5) modify ;;  # Call the modify function
    6) exit 0 ;;
    esac # End of case statement
    echo
done
