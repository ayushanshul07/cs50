<?php

// configuration
require("../includes/config.php"); 

$rows = query("SELECT * FROM history WHERE id = ?",$_SESSION["id"]);
$positions = [];
foreach ($rows as $row)
{
    $positions[] = [
        "symbol" => $row["symbol"],
        "shares" => $row["shares"],
        "price" => $row["price"],
        "transaction" => $row["transaction"],
        "time" => $row["time"]
    ]; 

}

// render portfolio
render("history.php", ["positions" => $positions , "title" => "History"]);

?>
