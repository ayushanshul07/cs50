-- MySQL dump 10.13  Distrib 5.5.44, for debian-linux-gnu (i686)
--
-- Host: localhost    Database: pset7
-- ------------------------------------------------------
-- Server version	5.5.44-0ubuntu0.14.04.1-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `history`
--

DROP TABLE IF EXISTS `history`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `history` (
  `id` int(10) unsigned NOT NULL,
  `symbol` varchar(50) COLLATE utf8_unicode_ci NOT NULL,
  `shares` int(20) unsigned NOT NULL,
  `price` double unsigned NOT NULL,
  `time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `transaction` varchar(10) COLLATE utf8_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `history`
--

LOCK TABLES `history` WRITE;
/*!40000 ALTER TABLE `history` DISABLE KEYS */;
INSERT INTO `history` VALUES (6,'ASDG',1000,0.002,'2015-08-29 13:58:33','BUY'),(12,'FREE',10,0.3779,'2015-08-29 14:03:11','BUY'),(12,'FREE',10,0.3779,'2015-08-29 14:04:36','SELL'),(12,'INFY',500,17.51,'2015-08-29 14:08:44','BUY'),(13,'FREE',2000,0.3779,'2015-08-29 15:15:07','BUY'),(16,'FREE',500,0.3779,'2015-08-29 17:02:23','BUY'),(16,'FREE',500,0.3779,'2015-08-29 17:09:05','SELL'),(18,'F',10,13.74,'2015-08-29 17:30:17','BUY'),(18,'F',10,13.74,'2015-08-29 17:30:30','SELL'),(16,'F',500,13.74,'2015-08-29 17:38:53','BUY'),(16,'F',500,13.74,'2015-08-29 17:42:54','SELL'),(16,'F',500,13.74,'2015-08-29 17:43:05','BUY'),(16,'F',500,13.74,'2015-08-29 17:45:07','SELL'),(16,'F',500,13.74,'2015-08-29 17:45:21','BUY'),(16,'F',200,13.74,'2015-08-29 17:50:54','BUY'),(16,'F',700,13.74,'2015-08-29 17:51:05','SELL');
/*!40000 ALTER TABLE `history` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `portfolios`
--

DROP TABLE IF EXISTS `portfolios`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `portfolios` (
  `id` int(10) unsigned NOT NULL,
  `symbol` varchar(50) COLLATE utf8_unicode_ci NOT NULL,
  `shares` int(20) unsigned NOT NULL,
  PRIMARY KEY (`id`,`symbol`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `portfolios`
--

LOCK TABLES `portfolios` WRITE;
/*!40000 ALTER TABLE `portfolios` DISABLE KEYS */;
INSERT INTO `portfolios` VALUES (6,'ASDG',1000),(12,'INFY',500),(13,'FREE',2000);
/*!40000 ALTER TABLE `portfolios` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `users` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `cash` decimal(65,4) unsigned NOT NULL DEFAULT '0.0000',
  `username` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `hash` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=19 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (1,10000.0000,'belindazeng','$1$50$oxJEDBo9KDStnrhtnSzir0'),(2,10000.0000,'caesar','$1$50$GHABNWBNE/o4VL7QjmQ6x0'),(3,10000.0000,'jharvard','$1$50$RX3wnAMNrGIbgzbRYrxM1/'),(4,10000.0000,'malan','$1$50$lJS9HiGK6sphej8c4bnbX.'),(5,10000.0000,'rob','$1$HA$l5llES7AEaz8ndmSo5Ig41'),(6,9998.0000,'skroob','$1$50$euBi4ugiJmbpIbvTTfmfI.'),(7,10000.0000,'zamyla','$1$50$uwfqB45ANW.9.6qaQ.DcF.'),(10,10000.0000,'Superbrain96','$1$vy2xXc93$W4/CJg7nyJtONnTVvKy6h0'),(11,10000.0000,'ranger','$1$V31f.kSJ$E5Em2x9WmAgLFSngRuew30'),(12,1245.0000,'nandanbedekar','$1$R6fNLXiJ$osLLxsoHOb4cQeGCu4e7A0'),(13,9244.2000,'niraj7017','$1$s2mD6P9q$NwowEVK3vTpCHiPunOYDl0'),(14,10000.0000,'ayushanshul07','$1$rZLniW.t$glHuvPW0n0waG/scpN9cb1'),(16,9870.0000,'ayush','$1$gQXsvEAR$s5s8j3k7n00cx7Jw2jLv8/'),(18,10000.0000,'aneesh','$1$76QCoFBy$ebHfEKa2Az0Q/WwBej1Ir0');
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2015-08-29 13:57:18
