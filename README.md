# QuickPass

This is a desktop application built on top of **C++** and **QT** to offer an interface where you can search for any string within a separated block of information in a text file to return that block of information where the queried text appeared.

It is intended to be an **Account & Password Launcher** but it technically works with any kind of information stored in a text file and separated by a common string, in this case three equal signs `===`.

![QuickPass Screenshot](screenshot.png)

### Features

* Read a simple `text/plain` file.
* Search block of information wrapped between a common _String_ (in this case `===`).
* Inline file content edition.
* **Edit Mode** utility to avoid unwanted modifications in the `TextView`.
* If the file `accounts.txt` doesn't exists, then **Edit Mode** is enabled automatically.
* Find multiple blocks with the same matching text searched.
* Reset `TextView` once the search field is emptied.

### TODO

* Account wizard.
* Accounts file encryptation.
* Password generator.
* Backups once **Edit Mode** is enabled.

### License

```
The MIT License (MIT)

Copyright (c) 2013 CIXTOR

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```
