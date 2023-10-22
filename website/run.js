const { exec } = require('child_process');

function runCppExecutable(ip) {
    // Replace 'your-executable' with the path to your C++ executable
    const executablePath = './out/build/client';

    // Execute the C++ executable with the vided IP address
    const command = `${executablePath} ${ip}`;

    exec(command, (error, stdout, stderr) => {
        if (error) {
            console.error(`Error: ${error.message}`);
            return;
        }
        if (stderr) {
            console.error(`C++ Error: ${stderr}`);
            return;
        }
        console.log(`C++ Output: ${stdout}`);
    });
}

function runCppExecutable() {
    const ip = document.getElementById('ip').value;
    runCppExecutable(ip);
}
