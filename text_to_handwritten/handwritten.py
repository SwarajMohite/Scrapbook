# pip install pywhatkit

import pywhatkit as pk


print("Welcome to the Text to Handwriting Converter! Made by Swaraj")
print("Please follow the prompts to create a handwritten image from your text.\n")
    
    
input_text = input("Paste the text you want to convert: ")
    
    
file_name = input("Enter the filename for the output image (e.g., handwritten.png): ")
    
   
if not file_name.lower().endswith('.png'):
        file_name = 'desktop/' + '.png' # This line will help to save image at desktop
    

print("Choose a color for the handwriting:")
print("1. Blue")
print("2. Red")
print("3. Green")
color_choice = input("Enter the number corresponding to your choice: ")
    
   
colors = {
        '1': [0, 0, 138],    # Blue
        '2': [255, 0, 0],    # Red
        '3': [0, 128, 0]     # Green
}
    
    # Default to blue if an invalid choice is made
color = colors.get(color_choice, [0, 0, 138])
    


try:
    pk.text_to_handwriting(input_text, file_name, color)
    print(f"Handwritten image successfully saved as '{file_name}' with color {color}.")
except Exception as e:
    print(f"An error occurred: {e}")
    
print("\nThank you for using the Text to Handwriting Converter!")

