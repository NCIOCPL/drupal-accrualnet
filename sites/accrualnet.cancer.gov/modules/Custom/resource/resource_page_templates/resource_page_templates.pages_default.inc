<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */


function resource_page_templates_default_page_manager_pages() {
    
        
    /********************************************************
     * Resources Page
     ********************************************************/
    $page = new stdClass();
    $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
    $page->api_version = 1;
    $page->name = 'resources_example';
    $page->task = 'page';
    $page->admin_title = 'Resources Example';
    $page->admin_description = '';
    $page->path = 'resources';
    $page->access = array();
    $page->menu = array();
    $page->arguments = array();
    $page->conf = array(
    'admin_paths' => FALSE,
    );
    $page->default_handlers = array();
    $handler = new stdClass();
    $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
    $handler->api_version = 1;
    $handler->name = 'page_resources_example_panel_context';
    $handler->task = 'page';
    $handler->subtask = 'resources_example';
    $handler->handler = 'panel_context';
    $handler->weight = 0;
    $handler->conf = array(
    'title' => 'Resources and Tools',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    );
    $display = new panels_display();
    $display->layout = 'onecol';
    $display->layout_settings = array();
    $display->panel_settings = array(
    'style_settings' => array(
        'default' => NULL,
        'middle' => NULL,
    ),
    );
    $display->cache = array();
    $display->title = 'Resources and Tools';
    $display->content = array();
    $display->panels = array();
    $display->hide_title = PANELS_TITLE_FIXED;
    $display->title_pane = '0';
    $handler->conf['display'] = $display;
    $page->default_handlers[$handler->name] = $handler;

    
    
    /****************************************************************
     * Level 2 Resource Page
     ****************************************************************/
    $page2 = new stdClass();
    $page2->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
    $page2->api_version = 1;
    $page2->name = 'resource_subpage';
    $page2->task = 'page';
    $page2->admin_title = 'Resource Subpage';
    $page2->admin_description = '';
    $page2->path = 'resources/%section';
    $page2->access = array();
    $page2->menu = array();
    $page2->arguments = array(
    'section' => array(
        'id' => 1,
        'identifier' => 'String',
        'name' => 'string',
        'settings' => array(
        'use_tail' => 0,
        ),
    ),
    );
    $page2->conf = array(
    'admin_paths' => FALSE,
    );
    $page2->default_handlers = array();
    $handler2 = new stdClass();
    $handler2->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
    $handler2->api_version = 1;
    $handler2->name = 'page_resource_subpage_panel_context';
    $handler2->task = 'page';
    $handler2->subtask = 'resource_subpage';
    $handler2->handler = 'panel_context';
    $handler2->weight = 0;
    $handler2->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    );
    $display2 = new panels_display();
    $display2->layout = 'twocol';
    $display2->layout_settings = array();
    $display2->panel_settings = array(
    'style_settings' => array(
        'default' => NULL,
        'left' => NULL,
        'right' => NULL,
    ),
    );
    $display2->cache = array();
    $display2->title = 'Sub Category';
    $display2->content = array();
    $display2->panels = array();
    $display2->hide_title = PANELS_TITLE_FIXED;
    $display2->title_pane = '0';
    $handler2->conf['display'] = $display2;
    $page2->default_handlers[$handler2->name] = $handler2;

    /*********************************************************
     * Level 3 Resource Page
     *******************************************************/
    $page3 = new stdClass();
    $page3->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
    $page3->api_version = 1;
    $page3->name = 'level_3_subpage';
    $page3->task = 'page';
    $page3->admin_title = 'Level 3 subpage';
    $page3->admin_description = '';
    $page3->path = 'resources/%section/%term';
    $page3->access = array();
    $page3->menu = array();
    $page3->arguments = array(
    'section' => array(
        'id' => 1,
        'identifier' => 'Vocab',
        'name' => 'string',
        'settings' => array(
        'use_tail' => 0,
        ),
    ),
    'term' => array(
        'id' => 2,
        'identifier' => 'Term',
        'name' => 'string',
        'settings' => array(
        'use_tail' => 0,
        ),
    ),
    );
    $page3->conf = array(
    'admin_paths' => FALSE,
    );
    $page3->default_handlers = array();
    $handler3 = new stdClass();
    $handler3->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
    $handler3->api_version = 1;
    $handler3->name = 'page_level_3_subpage_panel_context';
    $handler3->task = 'page';
    $handler3->subtask = 'level_3_subpage';
    $handler3->handler = 'panel_context';
    $handler3->weight = 0;
    $handler3->conf = array(
    'title' => 'Level 3',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    );
    $display3 = new panels_display();
    $display3->layout = 'threecol_25_50_25';
    $display3->layout_settings = array();
    $display3->panel_settings = array(
    'style_settings' => array(
        'default' => NULL,
        'left' => NULL,
        'middle' => NULL,
        'right' => NULL,
    ),
    );
    $display3->cache = array();
    $display3->title = 'Level 3';
    $display3->content = array();
    $display3->panels = array();
    $display3->hide_title = PANELS_TITLE_FIXED;
    $display3->title_pane = '0';
    $handler3->conf['display'] = $display3;
    $page3->default_handlers[$handler3->name] = $handler3;
    
    return array('resources' => $page,'resource_sub1' => $page2, 'resources_sub2' => $page3,);
}

?>