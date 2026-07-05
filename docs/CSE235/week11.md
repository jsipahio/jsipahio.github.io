# CSE235 Week 11: GUI Development with Tkinter
Tkinter is a GUI (graphical user interface) library that is bundled with Python. This means that no additional packages have to be installed to use Tkinter. Tkinter is cross-platform, allowing a GUI written in it to be used on any operating system that supports Python. Tkinter stands for "Tk interface"; it is a wrapper around the Tcl/Tk toolkit for creating GUIs.

## Tkinter Basics
The first thing to do to use Tkinter is to import it. Typically, Tkinter is aliased as `tk` to avoid writing the full name each time:
```py
import tkinter as tk
```
The `tk.Tk()` calls the Tkinter main window constructor, creating a new Tkinter window object. This object has several properties that can be set. The example below sets the title and size of the window.
```py
import tkinter as tk

# create a tkinter object
main_window = tk.Tk()
# set the title
main_window.title("Tkinter Example")
# set the dimensions of the window to be 500px by 350px
main_window.geometry("500x350")

# this causes the window to open
main_window.mainloop()
```
This will create a blank window. The minimize, maximize, and close buttons are already implemented by Tkinter. Tkinter defines "widgets" that allow you to add things like text boxes, buttons, input boxes, etc. to your GUI application. The main window itself is a widget. Widgets can be added directly to the main window, or added to other widgets to make nested designs. In the following sections, we'll look at the common Tkinter widgets:

### Generic Widget Methods
These methods are shared by all Tkinter widgets:  
- `pack()` - renders the widgets in a top to bottom stack. Can be passed a padding value to define how far from the edge of the window the widget should be placed.
- `grid()` - allows widgets to be rendered based on a row, column position
- `place()` - allows the literal pixel coordinates to be passed

### Label
The Label widget allows you to add text to the window. The `Label()` constructor is passed the window the widget will be attached to, the text to display, and the font to use. The `pack()` member function is used to render the widget on the window. The `pady` argument specifies the number of pixes to pad on the y-axis (vertical). In this case, we are specifying that at least 20 pixels of space should be left on the top and bottom of the label. The `padx` specifies the y-axis (horizontal) padding. This is set to 20 pixels as well.
```py
import tkinter as tk

main_window = tk.Tk()
main_window.title("Tkinter Example")
main_window.geometry("500x350")

# add a label to the window
label = tk.Label(main_window, text="Hello, World", font=("Arial", 16))
# render the lable on the window
label.pack(pady=20, padx=20)

main_window.mainloop()
```

### Button
The Button widget is used to create clickable buttons. The button constructor accepts the same arguments as label. However, it also supports an additional argument, `action`, for what to do when the button is clicked. Tkinter defines some predefined actions, but any function can be passed:
```py
import tkinter as tk

main_window = tk.Tk()
main_window.title("Tkinter Example")
main_window.geometry("500x350")

label = tk.Label(main_window, text="Hello, World", font=("Arial", 16))
label.pack(pady=20, padx=20)

# add a button to close the window
close_button = tk.Button(main_window, 
                        text="Close Window", 
                        font=("Arial", 16), 
                        command=main_window.quit)
# render the button below the label
close_button.pack(pady=10)

# function to increase a count
def increase_count():
    current_value = counter.get()
    counter.set(current_value + 1)

# create the count as a Tkinter IntVar
# this type handles telling the label that displays it to refresh
#  when the value changes
counter = tk.IntVar(value=0)
counter_label = tk.Label(main_window, textvariable=counter)
counter_label.pack(pady=20, padx=20)

# button to increase count
# it is passed the name of the function to increase the count
# we label the buttonn "Click Me!", since that is clearly trustworthy (sarcasm)
counter_button = tk.Button(main_window, 
                        text="Click Me!", 
                        font=("Arial", 16), 
                        command=increase_count)
counter_button.pack(pady=10)

main_window.mainloop()
```

### Message
A Tkinter Message is like a Label, but it will automatically wrap text to span multiple lines. If the text for a Label is too wide to fit on the screen, it will be cutoff. The Message widget has a predefined size, and will wrap text to stay within it's bounded size:
```py
import tkinter as tk

main_window = tk.Tk()
main_window.title("Tkinter Example")
main_window.geometry("500x350")

label_text = "This is a really long string. It will definitely be"
label_text += " too long to fit on the window without word wrapping"
label_text += ". See how the Label widget will cut it off."

# in this case, the text is too wide for the window, and will overflow
label = tk.Label(main_window, text=label_text, font=("Arial", 16))
label.pack(pady=20, padx=20)

main_window.mainloop()
```
As you can see, the text is cut off:  
![Image showing a Tkinter window with the text being cut off because of the label component being used](tkinter_label_text_too_long.png)  
If we use the Message widget instead, the text will be wrapped for us:
```py
import tkinter as tk

main_window = tk.Tk()
main_window.title("Tkinter Example")
main_window.geometry("500x350")

msg_text = "This is a really long string. It will definitely be"
msg_text += " too long to fit on the window without word wrapping"
msg_text += ". See how the Message widget will wrap the text."

# in this case, the Message component will wrap the text for us
msg = tk.Message(main_window, text=msg_text, font=("Arial", 16))
msg.pack(pady=20, padx=20)

main_window.mainloop()
```
Now, the text wraps, so the entire text content is readable:  
![Image showing a Tkinter windows with text wrapping thanks to the Message widget being used](tkinter_message_text_wrap.png)  

### Frame
A Frame is a generic container that can be used to hold other widgets. If you want to create a subsection for a window that has its own set of widgets, a Frame is used to store the widgets:  
```py
```

### LabelFrame
A LabelFrame is a widget which has 

### Menu

#### MenuButton

### Scrollbar

### Form Controls 

#### Entry

#### Text

### Listbox

#### Checkbutton

#### Spinbox

#### Scale 

### Tkinter Data Types
We saw some examples of the Tkinter data types (IntVar, StringVar) being used in some examples. Let's look more in-depth at the various data types Tkinter provides. 

## Tkinter Limitations

### ttk
Tkinter is extended by ttk (themed Tkinter), which allows for more modern designs to be created using Tkinter. One of the main critiques of Tk is that it's components are not easily styled and look very dated. Like Tkinter, ttk is included with 

## Conclusion
