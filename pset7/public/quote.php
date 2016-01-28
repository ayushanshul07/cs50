<?php

//configuration
require("../includes/config.php");

// if user reached page via GET (as by clicking a link or via redirect)
if ($_SERVER["REQUEST_METHOD"] == "GET")
{
    // else render form
    render("quote_form.php", ["title" => "Quote"]);
}

// else if user reached page via POST (as by submitting a form via POST)
else if ($_SERVER["REQUEST_METHOD"] == "POST")
{
    if(empty($_POST["symbol"]))
    {
        apologize("Please enter a symbol");
    }

    $stock = lookup($_POST["symbol"]);

    if($stock === false)
    {
        apologize("Qoute is not valid");
    }

    $stock["price"] = number_format($stock["price"] , 4 );

    render("quote.php", ["title" => "Quote" , "stock" => $stock ]);
}
?>
