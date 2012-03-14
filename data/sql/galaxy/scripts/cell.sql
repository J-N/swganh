
/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

CREATE TABLE IF NOT EXISTS `cell` (
  `id` bigint(20) NOT NULL,
  `cell_number` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  CONSTRAINT `FK_CB8787E2BF396750` FOREIGN KEY (`id`) REFERENCES `object` (`id`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

DELETE FROM `cell`;
    
/*!40000 ALTER TABLE `cell` DISABLE KEYS */;
/*!40000 ALTER TABLE `cell` ENABLE KEYS */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
