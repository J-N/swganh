/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET FOREIGN_KEY_CHECKS=0 */;

DROP PROCEDURE IF EXISTS `sp_PersistInstallation`;
DELIMITER //
CREATE PROCEDURE `sp_PersistInstallation`(IN `object_id` BIGINT, IN `selected_resource_id` BIGINT, IN `active_flag` TINYINT, IN `power_reserves` DOUBLE, IN `power_cost` DOUBLE, IN `max_extraction_rate` DOUBLE, IN `current_extraction_rate` DOUBLE, IN `current_hopper_size` DOUBLE, IN `is_updating` TINYINT, IN `condition_percentage` INT)
BEGIN
update installation i set i.selected_resource_id = selected_resource_id, i.is_active = active_flag, i.power_reserve = power_reserve, 
i.power_cost = power_cost, i.max_extraction_rate = extraction_rate, i.current_extraction_rate = current_extraction_rate, i.current_hopper_size = current_hopper_size,
i.is_updating = is_updating, i.condition_percentage = condition_percentage;
END//
DELIMITER ;
/*!40014 SET FOREIGN_KEY_CHECKS=1 */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
