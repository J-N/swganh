# --------------------------------------------------------
# Host:                         127.0.0.1
# Server version:               5.3.1-MariaDB
# Server OS:                    Win32
# HeidiSQL version:             6.0.0.3603
# Date/time:                    2011-10-16 19:38:43
# --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

use galaxy_manager;

# Dumping structure for procedure galaxy_manager.sp_CreateAccount
DELIMITER //
CREATE DEFINER=`root`@`localhost` PROCEDURE `sp_CreateAccount`(IN username char(32),IN password_ char(32), IN email varchar(50) )
BEGIN
DECLARE salt_ VARCHAR(50);
DECLARE saltedPASS VARCHAR(100);
DECLARE account_id INT;
SET salt_ = NOW()+username;
select SHA1(CONCAT(password_,'{',salt_,'}')) into saltedPASS;

INSERT INTO `account`
(`username`,
`username_canonical`,
`email`,
`email_canonical`,
`enabled`,
`salt`,
`password`,
`last_login`,
`locked`,
`expired`,
`roles`,
`credentials_expired`)
VALUES
(
username,username,email,email,1,salt_, saltedPASS, NOW(), 0, 0, '0', 0
);

select LAST_INSERT_ID();

END//
DELIMITER ;
/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
