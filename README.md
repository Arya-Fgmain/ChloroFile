# ChloroFile
<img src="website/img/fileleaf.png" alt="Your Image" width="150" height="200" />

Welcome to <i> ChloroFile</i>, a simple way to share files with people by exposing your vulnerable IP address for the world to see (patent pending). ChloroFile allows you to manage your files and share them seamlessly (real).

## Getting Started

To get started with ChloroFile, you can either access another myChloro or log into your own myChloro.

- **Access Another myChloro:** If you want to access files shared by others, click on "Access another myChloro" and enter the required IP address.

- **Log Into Your myChloro:** To manage your files and share them, click on "Log into your myChloro."

## Features

- **Drag-and-Drop Stickers:** You can add stickers to your ChloroFile by dragging and dropping them anywhere on the screen.

- **File Management:** Easily manage your files by adding, removing, and organizing them.

## How to Use

1. Open your ChloroFile.
2. Click on "Add" to add new files or drag-and-drop stickers on the screen.
3. To access files shared by others, click "Access another myChloro" and enter the IP address.

   Needs CMake and Boost Asio / Regular Asio.

## Backend setup guide

- __System requirements:__ It is recommended that you use __Linux, MacOS or other Unix-based systems__
- <a href="https://gcc.gnu.org/install/"> __GCC__ </a>
- __CMake__: CMake is required for running the backend of this project, try <a href="https://cmake.org/download/">this link</a> or install it via system-based package managers <a href="https://cgold.readthedocs.io/en/latest/first-step/installation.html">here</a>
- In the main project folder, first run "chmod +x *.sh" to give all the shell script files execution permissions
- Once done, run "./configure.sh && ./build.sh" to configure CMake and build the project. The compiled executables will be available in out/build.
- Run the out/build/server file "./out/build/server" and the out/build/client file "./out/build/client." After 10 seconds, you should see the server and client printing a connection message in the terminal. 

## Authors

<b> Arya Faghihy </b>

<b> Saarang Anand </b>

## Built With

- C++
- HTML
- CSS
- JavaScript

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- [Fall Hacks 2023](https://www.eventbrite.ca/e/fall-hacks-2023-tickets-735239048787?aff=oddtdtcreator)

## Contact

For any inquiries or support, feel free to contact the authors:

- [Arya Faghihy on GitHub](https://github.com/Arya-Fgmain)
- [Saarang Anand on GitHub](https://github.com/saaranganand)

Enjoy using ChloroFile!

<h3>Disclaimer:</h3>
ChloroFile is an independent project and is not affiliated with, endorsed by, or related to Google Drive or its parent company. This project is created for educational and demonstration purposes. Any similarities between ChloroFile and Google Drive are purely coincidental.
