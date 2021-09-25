# Contributing

Contents:
- [Inspiration](#Inspiration)
- [Development](#Development)
  - [Priorities](#Priorities)
    - [Efficiency](#Efficiency)
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

### Speedy Confirmation Dialogs

This needs to be some sort of way for users to easily select from multiple options. The example is for the filter viiew selection.
- Dialog with multiple options that can be set to specific keys
- Should look decently nice
- Should be able to handle shift keys as well that modify the dialog

### Preview Pane

There needs to be an optional pane across the bottom which is not very tall. Way to preview items before you scroll to them.
- Sideways listview of items where each item is a portrait of the file with the filename beneath it
- The current item should either always be on the right side or always in the center.
- The Preview Pane should key off of the sorting in the organizer. It should also have visible sorting options that change the organizers sort method
- `Y` can be the hotkey to sort (looks like a filter) [Sneedy Confirmation Dialog](#Speedy-Confirmation-Dialogs)
  - `S` sort by size
  - `D` sort by date
  - `F` sort by filetype
  - `Shift+KEY` sort descending (ascending by default)

### Group Actions

There should be a way for group actions. The behavior should be as follows
- `G` select/deselects current file
- All selected files should be highlighted in the [Preview Pane](#Preview-Pane)
- Actions should apply to all items
  - Move
  - Delete (Maybe don't support so people don't accidently nuke their folders? Or always show warning)
  - Rename (Rename group to `filename_1.png`, `filename_2.png`, `filename_3.png`)

### Hot Keys

I want to have programmable hot keys `0-9`. Would have limited functionality at first.
- There could also be some sort of "leader" key, perhaps `,`. Then you could hotkey `A-Z,0-9`
  - Would really only be necessary once scripting is in place

Hotkey actions:
- Move file to specific directory (ie. 1 ALWAYS moves to /path/to/meme/folder)
- [Scripting](#Scripting)

### Text Support

There should be a way to read text files. It should be inactive but the user should be able to highlight the text.
`C` - Copy Text (Don't just go ahead and do this. We may want `C` to be used for copying entire files but I'm not totally sure we need that in Syft)
`E` - Edit text

### PDF Support

There should be a way to read PDFs in this. May be able to use the webview already.
`W/S` - Scroll Down
`A/D` - Change Pages


### Scripting

Eventually I'd like there to be a way to scripting via `Python` and `bash`.

### Tag Database

The purpose of this is to be able to tag certain files with certain tags and be able to search your files for the tags.
The reasoning is perhaps you have two meme folders, `baseball`, and `funny`.
The meme you've saved is particularly funny, but it also has a baseball pun in it.
You do not know where to save this meme, because ostensibly the purpose of saving a meme is to retrieve it later, and you want to be sure you have it.
##### Solution: Tag the meme with `baseball` and `funny` so you will always be able to find it.


##### Workflow
- Type `T` to open tag pane for certain file
- Type tag and press `Enter` to add the tag
  - `T` opens pane with a text edit that allows you to enter a single tag and closes with `Enter`
  - `Shift+T` opens a larger pane that displays current tags for the file and allows you to enter multiple tags. Closes with `Esc`
  - `?` Opens a pane pops up and as I type, it populates out the files that either contain a tag of what I'm typing or is named what I'm typing.
    - `Enter` Ends search and enters results list
      - `J/K` Highlight Next/Previous file
        - `Enter` Move to file location

You would need a few tables

##### File
Field | Type
--- | ---
id | INT
filename | STR
hash_id | INT

##### Hash
Field | Type
--- | ---
id | INT
hash | STRI

##### Tag
Field | Type
--- | ---
id | INT
tag | STR

##### TagConnection
Field | Type
--- | ---
id | INT
file_id | INT
tag_id | INT

###### Note: Hash should not be utilized for text/code files.
They could be modified outside of Syft and then they would change. Therefore file movements may not be detected for txt files. Before adding a text file tag, there could be a warning that says something like:

```
Syft identifies tags by analyzing the content and names of the files. If you tag this file, the tags will only be recognized in the future if you:
- Do not modify the file contents
- Do not move or rename the file
```

##### File detection

For the issues that would inevitably arise from an ever-changing filesystem there would need to be a detection program that figures out what files are what files each time syft starts up.
This would necessitate some sort of scanning functionality that would need to happen in the background each time syft starts up.
We would want this to take as little time as possible, so only files that are tagged should be added to the database to reduce reduntant entries.

The process should be this
- For each file
  - Check that path exists
    - Yes: Check that hash is correct (might not be necessary)
    - No: Store Hash and File ID -> NOT_EXISTS
- For each Hash and File ID in NOT_EXISTS
  - Need to find a way to identify existing files
  - Phase 1: Directory Search
    - Get all filenames from the database
    - Get the directories the files are in (no duplicates)
    - Check each file against Hash in NOT_EXISTS (probably not worth checking if it's already in the DB, would take more time)
      - Match: Change the `filename` for the `file_id` that matches the hash in the DB
  - Phase 3: Subdirectory Search
    - Get directories from Phase 1
    - Search all subdirectories that haven't already been searched in the same way as Phase 1
    
    
