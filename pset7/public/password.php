<?php

//configuration
require("../includes/config.php");

// if user reached page via GET (as by clicking a link or via redirect)
if ($_SERVER["REQUEST_METHOD"] == "GET")
{
    // else render form
    render("newpassword.php", ["title" => "Change Password"]);
}

// else if user reached page via POST (as by submitting a form via POST)
else if ($_SERVER["REQUEST_METHOD"] == "POST")
{
    if(empty($_POST["oldpassword"]))
    {
        apologize("Please enter your old password.");
    }
    if(empty($_POST["newpassword"]))
    {
        apologize("Please enter your new password.");
    }
    if($_POST["newpassword"] != $_POST["confirmation"])
    {
        apologize("Passwords do not match.");
    }
    $array = query("SELECT hash FROM users WHERE id = ?",$_SESSION["id"]);
    if(crypt($_POST["oldpassword"], $array[0]["hash"]) == $array[0]["hash"])
    {
        query("UPDATE users SET hash = ? WHERE id = ?",crypt($_POST["newpassword"]) , $_SESSION["id"]);
        render("new.php", ["title" => "Success"]);
    }
    else
    {
        apologize("Password entered was incorrect.");
    }
}
?>
