# Contributing

I have a few long term goals that I would like to set out for this application. I say this to get hype for the program as well as to explain why certain decisions have been made for the application.

The main inspiration behind this was having a messy meme folder. I was tired of having to ctrl+click and drag and double click or do a long click to rename a file and double click to open a new preview window for every single meme I wanted to inspect. Being a vim user, I knew there was a more efficient way. For those of you who don't know what vim is, it is a text editor that is used for coding. As opposed to a normal text editor, where you have a line and can click, vim is purely keyboard based, meaning you do everything, including highlighting and scrolling, with the keyboard. By eliminating fine mouse movements and switching your hands from your keyboard to your mouse, you can be much more efficient.

## Feature Ideas

#### Speedy Confirmation Dialogs

This needs to be some sort of way for users to easily select from multiple options. The example is for the filter viiew selection.
- Dialog with multiple options that can be set to specific keys
- Should look decently nice
- Should be able to handle shift keys as well that modify the dialog

#### Preview Pane

There needs to be an optional pane across the bottom which is not very tall. Way to preview items before you scroll to them.
- Sideways listview of items where each item is a portrait of the file with the filename beneath it
- The current item should either always be on the right side or always in the center.
- The Preview Pane should key off of the sorting in the organizer. It should also have visible sorting options that change the organizers sort method
- `Y` can be the hotkey to sort (looks like a filter) [Dialog](#Speedy-Confirmation-Dialogs)
  - `S` sort by size
  - `D` sort by date
  - `F` sort by filetype
  - `Shift+KEY` sort descending (ascending by default)

#### Group Actions

There should be a way for group actions. The behavior should be as follows
- `G` select/deselects current file
- All selected files should be highlighted in the [Preview Pane](#Preview-Pane)
- Actions should apply to all items
  - Move
  - Delete (Maybe don't support so people don't accidently nuke their folders? Or always show warning)
  - Rename (Rename group to `filename_1.png`, `filename_2.png`, `filename_3.png`)

#### Hot Keys

I want to have programmable hot keys `0-9`. Would have limited functionality at first.
- There could also be some sort of "leader" key, perhaps `Q` to mimic vim. Then you could hotkey `A-Z`
  - Would really only be necessary once scripting is in place

Hotkey actions:
- Move file to specific directory (ie. 1 ALWAYS moves to /path/to/meme/folder)
- [Scripting](#Scripting)

#### Text Support

There should be a way to read text files. It should be inactive but the user should be able to highlight the text.
`C` - Copy Text (Don't just go ahead and do this. We may want `C` to be used for copying entire files but I'm not totally sure we need that in Syft)
`E` - Edit text

#### PDF Support

There should be a way to read PDFs in this. May be able to use the webview already.
`W/S` - Scroll Down
`A/D` - Change Pages


#### Scripting

Eventually I'd like there to be a way to scripting via `Python` and `bash`.

#### Tag Database

The purpose of this is to be able to tag certain files with certain tags and be able to search your files for the tags.

##### Workflow
- Type `T` to open tag pane for certain file
- Type tag and press `Enter` to add the tag
  - `T` opens pane with a text edit that allows you to enter a single tag and closes with `Enter`
  - `Shift+T` opens a larger pane that displays current tags for the file and allows you to enter multiple tags. Closes with `Esc`
  - `?` Opens a pane pops up and as I type, it populates out the files that either contain a tag of what I'm typing or is named what I'm typing.
    - `Shift+J`

You would need a few tables

##### File
Field | Type
--- | ---
id | INT
filename | STR
hash | STR

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
They could be modified outside of Syft and then they would change. Therefore file movements may not be detected for txt files.


