import pyttsx3  # Module to speak the text
from google_trans_new import google_translator # New Module to Translate.
from translate import Translator # To translate
import googletrans # Module to Translate
import speech_recognition as SR # Module for Speech functionality , We imported it as SR for Simplicity

def voice_translate():
    """
    Translate spoken language (english) to another language using google_translator and speech_recognition.
    """
    recognizer = SR.Recognizer()
    translator = google_translator()
    
    try:
        with SR.Microphone() as source:
            lang_choice = input("\nDo you want a list of language codes (y/n) to enter the language you are speaking: ")
            if lang_choice.lower() == "y":
                languages = googletrans.LANGUAGES
                print("Available languages:\n")
                for code, language in languages.items():
                    print(f"{language.title()}: {code}")

            lang_from = input("Enter the language code you are speaking: (en for English) : ")

            print("Clearing the background noise....")
            SpeakIT.say("Clearing the background noise....")
            SpeakIT.runAndWait()
            recognizer.adjust_for_ambient_noise(source, duration=1)

            print("Speak something...")
            SpeakIT.say("Speak something...")
            SpeakIT.runAndWait()
            audio = recognizer.listen(source, timeout=10)  # Increased timeout duration
            print("Done Recording...")
            SpeakIT.say("Done Recording...")
            SpeakIT.runAndWait()

        print("Recognizing speech...")
        SpeakIT.say("Recognizing speech...")
        SpeakIT.runAndWait()
        text = recognizer.recognize_google(audio, language=lang_from)
        print(f"You said: {text}")

        lang_choice = input("\nDo you want a list of language codes (y/n) to enter the desired language: ")

        if lang_choice.lower() == "y":
            for code, language in googletrans.LANGUAGES.items():
                print(f"{language.title()}: {code}")

        lang_to = input("Enter the target language code: (fr for french , mr for Marathi) : ")
        translator = Translator(from_lang=lang_from, to_lang=lang_to)
        translated = translator.translate(text)
        print(f"Translated text: {translated}")
        SpeakIT.say(translated)
        SpeakIT.runAndWait()
    
    except Exception as e:
        error = "Sorry! I couldn't translate the text!"
        print(f"{error} Error: {e}")
        SpeakIT.say(error)
        SpeakIT.runAndWait()

if __name__ == '__main__':
    """
    Main function. 
    """
    SpeakIT = pyttsx3.init()
    
    print("Welcome to Voice Translator!")
    SpeakIT.say("Welcome to Voice Translator!")
    SpeakIT.runAndWait()

    user_name = input("Please enter your name: ")
    SpeakIT.say(f"Hello, {user_name}!")
    SpeakIT.runAndWait()

    intro(user_name)

    while True:
        command = input("Enter the 1 for Start and 2 for Quit: ")
        my_commands(command)

        # calling different functions
        if command.lower() == "2":
            SpeakIT.say(f"Goodbye, {user_name}!")
            SpeakIT.runAndWait()
            break
        
        elif command.lower() == "1":
            voice_translate()
        else:
            SpeakIT.say("Wrong input!")
            SpeakIT.runAndWait()

