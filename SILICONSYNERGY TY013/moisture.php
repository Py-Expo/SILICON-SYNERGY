<?php 

$hostname = "localhost:3307"; 
$username = "root"; 
$password = ""; 
$database = "dht11"; 

$conn = mysqli_connect($hostname, $username, $password, $database);

if (!$conn) 
{ 
	die("Connection failed: " . mysqli_connect_error()); 
} 

else {
echo "Database connection is OK<br>"; }

// If values send by Arduino/NodeMCU are not empty then insert into MySQL database table

if(!empty($_POST['sendval']))
{
	$Moisturelevel = $_POST['sendval
	'];



// Update your tablename here
	$sql = "INSERT INTO moisture_sensor(Moisturelevel) VALUES (".$Moisturelevel.")"; 

	if ($conn->query($sql) === TRUE) {
		echo "Values inserted in MySQL database table.";
	} else {
		echo "Error: " . $sql . "<br>" . $conn->error;
	}
}


// Close MySQL connection
$conn->close();

?>