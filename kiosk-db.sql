-- --------------------------------------------------------
-- Host:                         localhost
-- Server version:               10.4.11-MariaDB - mariadb.org binary distribution
-- Server OS:                    Win64
-- HeidiSQL Version:             9.4.0.5125
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;


-- Dumping database structure for kiosk
CREATE DATABASE IF NOT EXISTS `kiosk` /*!40100 DEFAULT CHARACTER SET utf8mb4 */;
USE `kiosk`;

-- Dumping structure for table kiosk.items
CREATE TABLE IF NOT EXISTS `items` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `code` varchar(50) DEFAULT NULL,
  `name` varchar(50) DEFAULT NULL,
  `is_available` int(11) DEFAULT 1,
  `price` float(10,2) DEFAULT 0.00,
  `is_deleted` int(11) DEFAULT 0,
  `type` int(11) DEFAULT 1,
  PRIMARY KEY (`id`),
  UNIQUE KEY `code` (`code`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8mb4;

-- Dumping data for table kiosk.items: ~7 rows (approximately)
/*!40000 ALTER TABLE `items` DISABLE KEYS */;
INSERT INTO `items` (`id`, `code`, `name`, `is_available`, `price`, `is_deleted`, `type`) VALUES
	(1, 'F01', 'NASI GORENG MAMAK', 1, 0.00, 0, 0),
	(2, 'F02', 'NASI GORENG KAMPUNG', 1, 6.00, 0, 1),
	(3, 'D01', 'AIR KOSONG', 1, 0.30, 0, 2),
	(4, 'D02', 'MILO AIS', 1, 2.50, 0, 1),
	(5, 'D03', 'MILO PANAS', 1, 2.00, 0, 1),
	(6, 'F4', 'kolok', 1, 5.00, 0, 0),
	(7, 'D1', 'TEH O AIS', 1, 1.00, 0, 1);
/*!40000 ALTER TABLE `items` ENABLE KEYS */;

-- Dumping structure for table kiosk.orders
CREATE TABLE IF NOT EXISTS `orders` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `price` float DEFAULT 0,
  `status` int(11) DEFAULT 1,
  `discount_rate` int(11) DEFAULT 0,
  `after_discount` float DEFAULT 0,
  `created_at` datetime DEFAULT current_timestamp(),
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- Dumping data for table kiosk.orders: ~0 rows (approximately)
/*!40000 ALTER TABLE `orders` DISABLE KEYS */;
/*!40000 ALTER TABLE `orders` ENABLE KEYS */;

-- Dumping structure for table kiosk.order_items
CREATE TABLE IF NOT EXISTS `order_items` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `order_id` int(11) DEFAULT NULL,
  `item_id` int(11) DEFAULT NULL,
  `price` float(10,2) DEFAULT 0.00,
  `notes` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- Dumping data for table kiosk.order_items: ~0 rows (approximately)
/*!40000 ALTER TABLE `order_items` DISABLE KEYS */;
/*!40000 ALTER TABLE `order_items` ENABLE KEYS */;

-- Dumping structure for table kiosk.settings
CREATE TABLE IF NOT EXISTS `settings` (
  `happy_hour_active` int(11) DEFAULT 0,
  `discount_rate` int(11) DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- Dumping data for table kiosk.settings: ~0 rows (approximately)
/*!40000 ALTER TABLE `settings` DISABLE KEYS */;
INSERT INTO `settings` (`happy_hour_active`, `discount_rate`) VALUES
	(1, 30);
/*!40000 ALTER TABLE `settings` ENABLE KEYS */;

-- Dumping structure for table kiosk.staff
CREATE TABLE IF NOT EXISTS `staff` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(50) NOT NULL,
  `password` varchar(255) NOT NULL,
  `name` varchar(255) NOT NULL,
  `is_admin` int(11) NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb4;

-- Dumping data for table kiosk.staff: ~2 rows (approximately)
/*!40000 ALTER TABLE `staff` DISABLE KEYS */;
INSERT INTO `staff` (`id`, `username`, `password`, `name`, `is_admin`) VALUES
	(1, 'manager', '1234', 'AL MANAGER HUSAIN', 0),
	(2, 'admin', '1', '', 0);
/*!40000 ALTER TABLE `staff` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
