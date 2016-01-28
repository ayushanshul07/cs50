<?php

    require(__DIR__ . "/../includes/config.php");

    // ensure proper usage
    if (empty($_GET["geo"]))
    {
        http_response_code(400);
        exit;
    }

    // escape user's input
    $geo = urlencode($_GET["geo"]);

    // numerically indexed array of articles
    $articles = [];
    
     function curlFile($url,$proxy_ip,$proxy_port,$loginpassw)
    {

    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, $url);
    curl_setopt($ch, CURLOPT_HEADER, 0);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($ch, CURLOPT_PROXYPORT, $proxy_port);
    curl_setopt($ch, CURLOPT_PROXYTYPE, 'HTTP');
    curl_setopt($ch, CURLOPT_PROXY, $proxy_ip);
    curl_setopt($ch, CURLOPT_PROXYUSERPWD, $loginpassw);
    $data = curl_exec($ch);
    curl_close($ch);

    return $data;
    } 
    
    $loginpassw = 'ayush.anshul:madhepura';
    $proxy_ip = '202.141.80.22';
    $proxy_port = '3128';
    $url = "http://news.google.com/news?geo={$geo}&output=rss";

    $contents = curlFile($url,$proxy_ip,$proxy_port,$loginpassw);

    if ($contents === false)
    {
        http_response_code(503);
        exit;
    }

    // parse RSS
    $rss = @simplexml_load_string($contents);
    if ($rss === false)
    {
        http_response_code(500);
        exit;
    }

    // iterate over items in channel
    foreach ($rss->channel->item as $item)
    {
        // add article to array
        $articles[] = [
            "link" => (string) $item->link,
            "title" => (string) $item->title
        ];
    }

    // output articles as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($articles, JSON_PRETTY_PRINT));
    
   
?>
