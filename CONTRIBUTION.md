# Contributing

Contents:
- [Inspiration](#Inspiration)
- [Development](#Development)
  - [Priorities](#Priorities)
    - [Efficiency](#Efficiency)
    - [C++](#C++)
    - [Understandability](#Understandability)
      - [Command Explanations](#Command-Explanations)
  - [Feature Ideas](#Feature-Ideas)
    - [Speedy Confirmation Dialogs](#Speedy-Confirmation-Dialogs)
    - [Preview Pane](#Preview-Pane)
    - [Group Actions](#Group-Actions)
    - [Hot Keys](#Hot-Keys)
    - [Text Support](#Text-Support)
    - [PDF Support](#PDF-Support)
    - [Scripting](#Scripting)
    - [Tag Database](#Tag-Database)

### Inspiration

The main inspiration behind this was having a messy meme folder. I was tired of having to ctrl+click and drag and double click or do a long click to rename a file and double click to open a new preview window for every single meme I wanted to inspect. Being a vim user, I knew there was a more efficient way. For those of you who don't know what vim is, it is a text editor that is used for coding. As opposed to a normal text editor, where you have a line and can click, vim is purely keyboard based, meaning you do everything, including highlighting and scrolling, with the keyboard. By eliminating fine mouse movements and the time it takes to switch your hands from your keyboard to your mouse, you can be much more efficient. So I basically said "I want vim as a file explorer" and went to town.

## Development

###  Priorities

##### Efficiency
Syft is very **efficient** and that should always be priority number 1. How can we make it faster for the user to do the thing they want to do. The experience of someone new to Syft or unwilling to learn should always be an afterthought. In my eyes, if you use Syft but opt for mouse and GUI controls you are missing the point entirely, you will probably have a better experience using Finder or the File Explorer.

My initial thought was that if someone wants to create a sensible mouse GUI, then I would be fine with the PR and would merge it. However sometimes forcing the user to use something that is unwieldy will force them to look up and the command on their own, making them more efficient in the long run. I could really go either way on this one.

When I say _efficiency_ I really mean that the user should have to do very little.
If the user wants to do one thing, they press one button.
The types of operations that this program will be doing will be reading the contents of a directory and moving/renaming files, none of which are particularly CPU intensive, so on that end it's not too much of a worry for me.
Obviously larger things like the [Tag DB](#Tag-Database) would need to take these things into consideration and with things like [Scripting](#Scripting) we can offload the blame to the person who writes the script.

##### C++
I want at least all of the GUI and logic to be written in C++. I don't want any new widgets to be created with pyqt or something like that. C++ is already annoying enough to compile on it's own, let alone with Qt, and then adding more stuff just adds to the problem. I understand you can likely just modify the .pro but I everyone needs to install a bunch of new packages on their computer. We can do most of the things we need within C++/Qt.

In addition, I'd prefer if all views were created dynamically like how they're currently done as opposed to using some sort of `.ui` qt file. I've never used them and I don't know enough about them and I'd rather stay away.

##### Understandability
Despite having many different commands for different files, I want there to be some sense of consistency in the commands, and some commands may need to be re-assessed. I like each command to have a 1-step logical jump to the command. It may sound dumb but it works.

Examples:

"Oh I've selected a `webm` file, and I'd like to view it in my default `Program`. I remember! `Program` starts with `P` and that is the command"

"I'd like to change my active directory filtering, how do I open that again? Oh yes, a filter/funnel is shaped like a `Y` and that is the command" (not implemented yet)

###### Command Explanations

Key | Command | Explanation
--- | --- | ---
`J/K` | Up/Down | Changing images is one of the primary movements and the users hand should remain on the home row.
`WASD`| Move around | Move in an image, as well as using `A/D` to scroll through a video and `W/S` to scroll through a pdf and `A/D` to change pdf pages. These all stem from the standard `WASD` directional movement. I think this is intuitive enough for people to figure out.
`R` | Rename | `R` and if someone is familiar with `WASD` it would be the same as the "Reload" control. Same for directories when in directory view.
`I/O` | Zoom in/out | "In" and "Out" start with `I/O` and the keys are right beside eachother and near `J/K`
`U` | Undo | Starts with `U`.  It's also near `J/K/I/O`. `Shift+U` for undo I don't like that much but I think it's fine. Just don't make mistakes.
`Z` | Mute | `Z` for "Zip it"
`/` | Open Directory | `/` denotes a directory. Near `.`
`.` | Up a directory | In the terminal `..` is up a directory. Near `/`
`N` | New Directory | New starts with `N`. Near `M` and both activate the Directory Pane
`N` | Move File/Directory | Move starts with `M`. Near `N` and both activate the Directory Pane
`P` | Open in default | Uses default `P`rogram to open the file

### Permissions

I hope anybody that wants to help can help. If for some reason you can't clone the repo or create a PR let me know or create an issue I'll see if I can sort it out. I will get to these features over time. Unless someone beats me to implementation I will develop them. The priority at the moment is the clean up the current [Issues](https://github.com/syftking/syft/issues).

The one thing that I absolutely positively definitely will not do myself is [change the appearance](#https://github.com/syftking/syft/issues/2). I don't know enough about qt styling and I don't care to know more about it.

## Feature Ideas

I have a few long term goals that I would like to set out for this application. I say this to get hype for the program as well as to explain why certain decisions have been made for the application.

If anyone would like to implement any of these, feel free.

### Speedy Confirmation Dialogs

[Issue #19](https://github.com/syftking/syft/issues/19)

### Preview Pane

[Issue #13](https://github.com/syftking/syft/issues/13)

### Group Actions

[Issue #14](https://github.com/syftking/syft/issues/14)

### Hot Keys

[Issue #15](https://github.com/syftking/syft/issues/15)


### Text Support

[Issue #16](https://github.com/syftking/syft/issues/16)

### PDF Support

[Issue #17](https://github.com/syftking/syft/issues/17)

### Tag Database

[Issue #18](https://github.com/syftking/syft/issues/18)

