import tkinter as tk
from tkinter import filedialog, Text, messagebox
import os
import PySimpleGUI as sg

def create_text_editor():
    layout = [[sg.Menu([['File', ['Open', 'Save', 'Save As', 'Exit']],
                        ['Edit', ['Copy', 'Paste']]])],
              [sg.Multiline(size=(80, 20), key='-TEXTBOX-')]]

    window = sg.Window('Text Editor', layout, finalize=True)
    text_widget = window['-TEXTBOX-']

    while True:
        event, values = window.read()

        if event in (sg.WIN_CLOSED, 'Exit'):
            break
        elif event == 'Open':
            filename = filedialog.askopenfilename(initialdir="/", title="Select file",
                                                   filetypes=(("Text files", "*.txt"), ("All files", "*.*")))
            if filename:
                with open(filename, "r") as file:
                    text_widget.update(value=file.read())
        elif event == 'Save':
            filename = getattr(window, 'filename', None)
            if filename:
                with open(filename, "w") as file:
                    file.write(values['-TEXTBOX-'])
            else:
                save_as(window, values['-TEXTBOX-'])
        elif event == 'Save As':
            save_as(window, values['-TEXTBOX-'])
        elif event == 'Copy':
            text_widget.Widget.event_generate("<<Copy>>")
        elif event == 'Paste':
            text_widget.Widget.event_generate("<<Paste>>")

    window.close()

def save_as(window, content):
    filename = filedialog.asksaveasfilename(defaultextension=".txt", filetypes=(("Text files", "*.txt"), ("All files", "*.*")))
    if filename:
        window.filename = filename
        with open(filename, "w") as file:
            file.write(content)

if __name__ == "__main__":
    create_text_editor()

