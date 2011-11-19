# --------------------------------------------------------
# Host:                         127.0.0.1
# Server version:               5.3.1-MariaDB
# Server OS:                    Win32
# HeidiSQL version:             6.0.0.3603
# Date/time:                    2011-10-16 19:39:50
# --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

use galaxy;

# Dumping structure for table galaxy.installation
CREATE TABLE IF NOT EXISTS `installation` (
  `id` bigint(20) NOT NULL,
  `selected_resource_id` bigint(20) DEFAULT NULL,
  `is_active` tinyint(1) NOT NULL,
  `power_reserve` double NOT NULL,
  `power_cost` double NOT NULL,
  `max_extraction_rate` double NOT NULL,
  `current_extraction_rate` double NOT NULL,
  `current_hopper_size` double NOT NULL,
  `is_updating` tinyint(1) NOT NULL,
  `condition_percentage` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `IDX_1CBA6AB1B006AEA3` (`selected_resource_id`),
  CONSTRAINT `FK_1CBA6AB1B006AEA3` FOREIGN KEY (`selected_resource_id`) REFERENCES `resource` (`id`),
  CONSTRAINT `FK_1CBA6AB1BF396750` FOREIGN KEY (`id`) REFERENCES `object` (`id`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

# Dumping data for table galaxy.installation: ~0 rows (approximately)
DELETE FROM `installation`;
/*!40000 ALTER TABLE `installation` DISABLE KEYS */;
/*!40000 ALTER TABLE `installation` ENABLE KEYS */;
/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
