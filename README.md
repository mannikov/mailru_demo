# Mail.ru demo source
Use this code exampe as a guideline for making the program for mail.ru email fetching.
This example connects to pop3 server, fetches all emails and outputs the basic email information (ID, Size, From, Subject, Date).

## Requirements
Microsoft Visual Studio 2012 or higher

## Installation
1. Clone the repository to your computer or download and extract zip file.
2. Open and build solution.
3. Go to Release (or Debug) folder and run `mailru_demo.exe`.

## Usage
Run program with 2 parameters: `mailru_demo.exe email password`
* email: mail.ru email address like xxx@mail.ru
* password: account password

## Dependencies
This project uses [POCO C++ library](http://pocoproject.org/) and OpenSSL.
All needed files (headers, libs and dlls) are included to this repository and you can make a fast start.
If you want to extend application functionality, download POCO libraries from the link above.

## License
licensed under the [Boost Software License](https://spdx.org/licenses/BSL-1.0).
