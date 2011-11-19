# --------------------------------------------------------
# Host:                         127.0.0.1
# Server version:               5.3.1-MariaDB
# Server OS:                    Win32
# HeidiSQL version:             6.0.0.3603
# Date/time:                    2011-10-16 19:38:42
# --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

use galaxy_manager;

# Dumping structure for table galaxy_manager.account_session
CREATE TABLE IF NOT EXISTS `account_session` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `account` int(11) NOT NULL,
  `session_key` varchar(100) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=24 DEFAULT CHARSET=latin1;

# Dumping data for table galaxy_manager.account_session: ~23 rows (approximately)
DELETE FROM `account_session`;
/*!40000 ALTER TABLE `account_session` DISABLE KEYS */;
/*!40000 ALTER TABLE `account_session` ENABLE KEYS */;
/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
