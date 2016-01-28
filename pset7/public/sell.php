<?php

//configuration
require("../includes/config.php");

// if user reached page via GET (as by clicking a link or via redirect)
if ($_SERVER["REQUEST_METHOD"] == "GET")
{
    $rows = query("SELECT * FROM portfolios WHERE id = ?",$_SESSION["id"]);
    $positions = [];

    foreach ($rows as $row)
    {
        $positions[] = [ "symbol" => $row["symbol"] ]; 
    }

    // else render form

    render("sell_form.php", ["positions" => $positions , "title" => "Sell" , ]);
}

// else if user reached page via POST (as by submitting a form via POST)
else if ($_SERVER["REQUEST_METHOD"] == "POST")
{
    $symbol = strtoupper($_POST["sell"]);
    if(empty($symbol))
    {
        apologize("Please enter a symbol.");
    }
    $row = query("SELECT shares FROM portfolios WHERE symbol = ? AND id = ?",$_POST["sell"] ,$_SESSION["id"]);

    $stock = lookup($symbol);

    $money = $stock["price"] * $row[0]["shares"];

    query("DELETE FROM portfolios WHERE symbol = ? AND id = ?",$_POST["sell"] ,$_SESSION["id"]);
    query("UPDATE users SET cash = cash + ? WHERE id = ?",$money , $_SESSION["id"]);  

    query("INSERT INTO history (id, symbol, shares, price , time , transaction) VALUES(?, ?, ? , ? , NOW() , ?)",$_SESSION["id"],$symbol,$row[0]["shares"],$stock["price"],"SELL");         

    redirect("/");


}
?>
