import serial
import sys
import time
import os
import time
import playsound
import speech_recognition as sr
from gtts import gTTS

node_mode = b'\xFF'
magic_mode = b'\x00'
temperature_mode = b'\x01'
humidity_mode = b'\x02'
flame_mode = b'\x03'

cntVoice = 0

def Speak(text):
    global cntVoice

    print(text)
    tts = gTTS(text=text, lang="en")
    filename = "controller\\temp\\voice{}.mp3".format(cntVoice)
    cntVoice += 1
    tts.save(filename)
    playsound.playsound(filename)

def GetAudio():
    r = sr.Recognizer()
    with sr.Microphone(device_index=1) as source:
        print("[Speak now]")
        audio = r.listen(source, phrase_time_limit=3)
        print("[End listening]")
        said = ""

        try:
            said = r.recognize_google(audio)
            print("> " + said)
        except:
            return "nada"

    return said

def main():
    arduino = serial.Serial("COM6", 9600)
    mode = node_mode
    global cntVoice
    cntVoice = 0

    data = arduino.readline()[:-2]
    data = str(data, "UTF-8")
    if "Arduino Configured" in data:
        Speak("Hi there, I am Condor Ruben's project! Press any key to listen")

    while True:
        input("[Press any key to listen]")

        text = GetAudio()
        if "temperature" in text:
            mode = temperature_mode
        elif "humidity" in text:
            mode = humidity_mode
        elif "game" in text or "magic" in text:
            Speak("Move the board left and right")
            mode = magic_mode
        elif "flame" in text or "fire" in text:
            Speak("Checking...")
            mode = flame_mode
        else:
            mode = node_mode
            if "nada" in text:
                continue
            elif "thank" in text:
                Speak("You're welcome")
                continue
            elif "hello" in text:
                Speak("Hello")
                continue
            elif "exit" in text:
                Speak("Exiting...")
                time.sleep(1)
                sys.exit()
            else:
                Speak("Please repeat. I didn't get that")

        arduino.write(mode)

        data = arduino.readline()[:-2]
        data = str(data, "UTF-8")
        if data:
            if "None Mode" not in data:
                Speak(data)
        

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        sys.exit()
    