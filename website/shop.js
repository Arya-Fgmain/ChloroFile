const fileList = document.getElementById("file-list");
const addFileButton = document.getElementById("add-file");
const fileInput = document.getElementById("file-input");

// Array to store files
const files = [];

// Function to add a new file
function addFile() {
    fileInput.click(); // Trigger the hidden file input element
}

// Function to handle file selection
function handleFileSelect(event) {
    const selectedFile = event.target.files[0];
    if (selectedFile) {
        files.push(selectedFile.name);
        displayFiles();
    }
    // Clear the file input to allow selecting the same file multiple times
    fileInput.value = "";
}

// Function to remove a file
function removeFile(index) {
    files.splice(index, 1);
    displayFiles();
}

// Function to display files
function displayFiles() {
    fileList.innerHTML = ""; // Clear the list
    files.forEach((file, index) => {
        const listItem = document.createElement("li");
        listItem.innerHTML = `${file} <button onclick="removeFile(${index})">Remove</button>`;
        fileList.appendChild(listItem);
    });
}

// Event listener for the "Add" button
addFileButton.addEventListener("click", addFile);

// Event listener for file input changes
fileInput.addEventListener("change", handleFileSelect);

// Initial display of files
displayFiles();
