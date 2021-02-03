<html>
 <head>
  <title>[title of your website]</title>
 </head>
 <body>
<?php

$password="[your netatmo account password";
$username="[your netatmo account email]";
$app_id = "[your app id see 'my apps' on https://dev.netatmo.com/]";
$app_secret ="[your app secret]";

$token_url = "https://api.netatmo.com/oauth2/token";
$postdata = http_build_query(
        array(
            'grant_type' => "password",
            'client_id' => $app_id,
            'client_secret' => $app_secret,
            'username' => $username,
            'password' => $password,
            'scope' => "read_thermostat"
    )
);

$opts = array('http' =>
    array(
        'method'  => 'POST',
        'header'  => 'Content-type: application/x-www-form-urlencoded',
        'content' => $postdata
    )
);

$context  = stream_context_create($opts);
$response = file_get_contents($token_url, false, $context);

$params = null;
$params = json_decode($response, true);

//var_dump ($params);

// =========== GET REAL TIME DATA =================

$station_url = "https://api.netatmo.com/api/homestatus?home_id=[YOUR HOME ID HERE]&access_token=" . $params['access_token']; // DONT FORGET TO ADD YOUR HOME ID HERE
$requete = file_get_contents($station_url);
$json_stations_data = json_decode($requete,true);



//print_r(array_values($json_stations_data)); uncomment if you want to read the whole response
//print_r($requete);
echo ("actuele temperatuur ");
echo $json_stations_data["body"]["home"]["rooms"][1]["therm_measured_temperature"]; 		//temp measured
echo (", ingestelde temperatuur ");
echo $json_stations_data["body"]["home"]["rooms"][1]["therm_setpoint_temperature"];  		//temp setpoint
echo (", anticipating? ");
if  ($json_stations_data ["body"]["home"]["rooms"][1]["anticipating"]==true){  		//anticipating?
echo ("1.");
}
else{
    echo("0.");
}



?>
 </body>
</html>