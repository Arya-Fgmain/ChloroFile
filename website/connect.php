<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // Get the IP address entered by the user
    $ip = $_POST["ip"];

    // Validate the IP address if needed

    // Run the C++ executable with the IP address
    $output = shell_exec("./out/build/client $ip");

    // Output the result to the user
    echo "C++ Output: " . $output;
}
?>