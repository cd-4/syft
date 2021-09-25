# Syft
A program for optimal file browsing, renaming, and movement.

With minimal keystrokes, you can rename files, create directories, move files, preview files with Syft.

### Contents
- [Welcome](#Welcome)
- [Installation](#Installation)
- [Startup](#Startup)
- [Commands](#Commands)
   - [Content View](#Content-View)
   - [Directory View](#Directory-View)
- [Donations](#Donations)


##### Welcome
This was designed out of necessity, since my meme folder was becoming unwieldy. For that reason, there isn't much fluff on the program.
It was designed for quick filtering and sorting of files, not for optimally viewing the files, or to look good.
What that means is a significant portion of the actions are done with the keyboard and there simply aren't options for using the mouse, and it also uses the default Qt appearance.

![There should be a screenshot here!](https://github.com/syftking/syft/blob/main/sample.png?raw=true)


### New Features
If you wish to see any features, I suggest you create an issue and pray that someone decides to take it up, or implement it yourself and create a pull request.
I am open to any new features and PRs.

# Installation

Currently, the only way to run Syft is to build it yourself.
To do so, follow these steps:

- 1) Download [Qt Creator](https://www.qt.io/product/development-tools) and install the latest version of Qt
- 2) Open the `syft.pro` file in Qt Creator
- 3) Build the project
- **Note**: You may need to specify QT_PLUGIN_PATH within Qt Creator.
  - For me, I could fix this by looking in my Build Environment in Qt Creator, and choosing environment variables
  - The value QTDIR should be pre-populated. Simply set the QT_PLUGIN_PATH to "$QTDIR/plugins" (not actually $QTDIR but the full path)

# Startup

Here is a simple guide on how to work this.
1) Start Syft
2) Press `/` and select the directory which contains your unorganized memes
3) On the left is a list of subdirectories
4) On the right, is the content viewer, where you can view your files
5) On the top is the name of the file
6) See [Commands](#Commands) to interact with the files

## Usage

The usages was designed to be effective once you know how to use it. Some commands are only applicable to Images, some are only applicable to Videos.

###### Note:
- Do not click anywhere in the Content Viewer. You will not be able to change files afterwards. If you click there, simply click outside of the content view inside the window and it should revert back to normal. [See Issue #4](https://github.com/syftking/syft/issues/4)

- Webm files do not yet support scrubbing and restarting. Simply change files to restart [See Issue #5](https://github.com/syftking/syft/issues/5)



# Commands

This is the general control scheme. They have different contexts but this is what you need in your head.

I strongly suggest you read all of these because you simply cannot do most actions without knowing the key commands and there is no help via the GUI at this time.

Key | Action
--- | ---
`Esc` | Cancel
`J/K` | Next/Previous 
`R` | Rename
`WASD` | Move
`U` | Undo
`Shift+U` | Redo



## Content View

The content view is the main area that displays the file contents.

Key | Action
--- | ---
`Esc` | Reset Image Position [Image] / Reset Video [Video]
`J/K` | Next/Previous File
`R` | Rename File. `Enter` to confirm, `Esc` to cancel.
`I/O` | Zoom In/Out [Image Only]
`WASD` | Move Image [Image Only]
`A/S` | Step Back/Forward [Video Only]
`Z` | Toggle Mute [Video Only] (Videos always start muted)
`/` | Select New Directory [Opens Dialog]
`.` | Navigate Up a Directory
`N` | New Directory. `Enter` to confirm, `Esc` to cancel. [Enters Directory View]
`M` | Move [Enters Directory View]
`Delete/Backspace` | Delete File [Warning Dialog. Cannot be undone]
`P` | Open file in default program
`Space` | Start/Pause Video [Video Only]



## Directory View

The directory view is the pane on the left which has the names of subdirectories.

Key | Action
--- | ---
`Esc` | Cancel action. Return to Content View.
`J/K` | Next/Previous subirectory.
`Enter` | Move current file to highlighted subdirectory
`Shift+Enter` | Navigate to highlighted subdirectory
`R` | Rename highlighted directory. `Enter` to confirm, `Esc` to cancel.
`N` | New Directory. `Enter` to confirm, `Esc` to cancel.

### Donations

BTC: `bc1qy6gvsa02st4exneg244gx9l557fuj7mlu3en7n`

ETH: `0x8A05d9f1A483A71C7AfeCF498eEd980168535F70`

XMR: `47jkn6ND2mG8KtrFQPUtvp4WoVGWnwB571dogvcKd68AJMKiijraKJGb1NE2TxrdyN7gbqNTP3tU1cNb5khjrzNyU3Jezzz`

