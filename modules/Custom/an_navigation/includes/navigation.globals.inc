<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
$GLOBALS['an_navigation_information'] = array(
    'menu_name' => t('an-main-nav'),
    'title' => t('AccrualNet Main Navigation'),
    'description' => t('Provides navigation for the AccrualNet Site.')
);



$GLOBALS['an_navigation'] = array(
	'protocol_accrual_lifecycle' => array(
                    'weight' => '0',
                    'link_title' => t('Protocol Accrual Lifecycle'),
                    'link_path' => t('protocol_accrual_lifecycle'),
                    'mlid' => 0,
                    
            ),
    
	'communities' => array(
                    'weight' => '1',
                    'link_title' => t('Communities'),
                    'link_path' => t('node/1'),
                    'mlid' => 0,
                    
                        
            ),
	'literature' => array(
                    'weight' => '2',
                    'link_title' => t('Literature & Tools'),
                    'link_path' => t('literature'),
                    'mlid' => 0,
             
            ),
	'education_and_training' => array(
                    'weight' => '3',
                    'link_title' => t('Education & Training'),
                    'link_path' => t('http://localhost/node/25'),
                    'mlid' => 0,           
            ),
	
);
?>
