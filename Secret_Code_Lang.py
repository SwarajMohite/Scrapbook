import string 
import random

# Code
def code(): 
    message=input("Enter your Message to code here: ")
    words=message.split(" ")
    coded=[]
    N=3
    for word in words:
        if(len(word)>=3):
            list=''.join(random.choices(string.ascii_lowercase, k=N))+word[1:]+word[0]+''.join(random.choices(string.ascii_lowercase, k=N))
            coded.append(list)
        else:
            coded.append(word[::-1])
    print(" ".join(coded))


# Decode
def Decode():
    message=input("Enter your Message to decode here: ")
    words=message.split(" ")
    decoded=[]
    for word in words:
        if(len(word)>=3):
            list=word[3:-3]
            list=list[-1]+list[:-1]
            decoded.append(list)
        else:
            decoded.append(word[::-1])
    print(" ".join(decoded))


# Main
def main():
    print("Welcome to Secret Code Lab\n")
    while True:
        choice = input("\nEnter \n 1 for Message to Code\n 2 for Decoding the message\n 0 to Quit\n:")
        if choice == "0":
            print("Thanks for visiting us. :)")
            break
        elif choice == "1":
            code()
        elif choice == "2":
            Decode()
        else:
            print("Invalid choice! Try again!")

main()
