<?php

//configuration
require("../includes/config.php");

// if user reached page via GET (as by clicking a link or via redirect)
if ($_SERVER["REQUEST_METHOD"] == "GET")
{
    // else render form
    render("register_form.php", ["title" => "Register"]);
}

// else if user reached page via POST (as by submitting a form via POST)
else if ($_SERVER["REQUEST_METHOD"] == "POST")
{
    if(empty($_POST["username"]))
    {
        apologize("You must choose a username.");
    }
    if(empty($_POST["password"]))
    {
        apologize("You must set a password.");
    }
    if($_POST["password"] != $_POST["confirmation"])
    {
        apologize("Passwords do not match.");
    }

    $result = query("INSERT INTO users (username , hash , cash ) VALUES ( ? , ? , 10000.0000)" , $_POST["username"] , crypt($_POST["password"]));

    if($result === false)
    {
        apologize("Sorry username already exists");
    }            

    $rows = query("SELECT LAST_INSERT_ID() AS id");
    $_SESSION["id"] = $rows[0]["id"];

    redirect("/");

}
?>
