<?php

/**
 * @file
 * Contains functions to alter Drupal's markup for the AccrualNet theme.
 *
 */
// Auto-rebuild the theme registry during theme development.
if (theme_get_setting('accrualnet_rebuild_registry') && !defined('MAINTENANCE_MODE')) {
	// Rebuild .info data.
	system_rebuild_theme_data();
	// Rebuild theme registry.
	drupal_theme_rebuild();
}

/**
 * Implements HOOK_theme().
 */
function accrualnet_theme(&$existing, $type, $theme, $path) {
	include_once './' . drupal_get_path('theme', 'accrualnet') . '/accrualnet-internals/template.theme-registry.inc';
	$items = _accrualnet_theme($existing, $type, $theme, $path);

	$items['user_login'] = array(
		'render element' => 'form',
		'path' => drupal_get_path('theme', 'accrualnet') . '/templates',
		'template' => 'user-login',
		'preprocess functions' => array(
			'accrualnet_preprocess_user_login'
		),
	);
	$items['user_pass'] = array(
		'render element' => 'form',
		'path' => drupal_get_path('theme', 'accrualnet') . '/templates',
		'template' => 'user-pass',
		'preprocess functions' => array(
			'accrualnet_preprocess_user_pass'
		),
	);
	$items['user_register_form'] = array(
		'render element' => 'form',
		'path' => drupal_get_path('theme', 'accrualnet') . '/templates',
		'template' => 'user-register-form',
		'preprocess functions' => array(
			'accrualnet_preprocess_user_register_form'
		),
	);
	$items['user_profile_form'] = array(
		'render element' => 'form',
		'path' => drupal_get_path('theme', 'accrualnet') . '/templates',
		'template' => 'user-profile-form',
		'preprocess functions' => array(
			'accrualnet_preprocess_user_profile_form'
		),
	);

	return $items;
}

function accrualnet_preprocess_user_profile(&$vars) {
    /*
	$profile = &$vars['user_profile'];

	hide($profile['summary']);

	$work_email = $vars['user']->mail;

	$profile['field_work_email'] = array(
		'#theme' => 'field',
		'#title' => t('WORK EMAIL'),
		'#weight' => -2,
		'#items' => array(0 => array('value' => $work_email)),
		0 => array('#markup' => $work_email),
	);

	if (isset($profile['field_role'])) {
		$profile['field_role']['#title'] = t('OCCUPATION');
		$profile['field_role']['#weight'] = 4;
	}
	if (isset($profile['field_years_in_research'])) {
		$profile['field_years_in_research']['#title'] = t('YEARS OF CLINICAL RESEARCH');
		$profile['field_years_in_research']['#weight'] = 5;
	}
	if (isset($profile['field_institution_type'])) {
		$profile['field_institution_type']['#title'] = t('INSTITUTION TYPE');
		$profile['field_institution_type']['#weight'] = 6;
	}
	if (isset($profile['field_areas_of_interest'])) {
		$profile['field_areas_of_interest']['#title'] = t('AREAS OF INTEREST');
		$profile['field_areas_of_interest']['#weight'] = 7;
	}
*/

}

function accrualnet_preprocess_user_picture(&$vars) {

}

function accrualnet_preprocess_user_profile_item(&$vars) {

}

function accrualnet_preprocess_user_login(&$vars) {

}

function accrualnet_preprocess_user_pass(&$vars) {

}

function accrualnet_preprocess_user_register_form(&$vars) {
    $vars['form']['account']['name']['#title'] = "";
    $vars['form']['picture']['picture_upload']['#description'] = "You can upload a JPG, GIF, or PNG file.\n(File size limit is 2MB)";
    $vars['form']['account']['name']['#description'] ='This username will be displayed to all registered users if you participate in conversations or make comments on resources';
    $vars['form']['picture']['picture_upload']['#size'] = 0;
                    $vars['form']['profile_color']['und']['#description'] = '';
/*
	$vars['form']['account']['pass']['#title'] = t('Password');
	unset($vars['form']['account']['pass']['pass1']['#title']);
	unset($vars['form']['account']['pass']['pass2']['#title']);

	unset($vars['form']['picture']['#theme_wrappers']);
	unset($vars['form']['picture']['select_avatar']['#title']);

	$elements = array(
		array(
			'element' => & $vars['form']['account']['name'],
			'desc' => 'This username will be displayed to all registered users ' .
			'if you participate in conversations or make comments on resources.'
		),
		array(
			'element' => & $vars['form']['account']['mail'],
			'desc' => 'Please enter a professional email address.'
		),
		array(
			'element' => & $vars['form']['account']['pass'],
			'desc' => 'Please enter a password containing both letters and numbers.'
		),
		array(
			'element' => & $vars['form']['field_role']['und']['select'],
			'desc' => 'Please select from the list the description that best ' .
			'describes your occupation.'
		),
		array(
			'element' => & $vars['form']['field_years_in_research']['und'],
			'desc' => 'Please enter the number of years in your field or at ' .
			'your institution.'
		),
		array(
			'element' => & $vars['form']['field_institution_type']['und']['select'],
			'desc' => 'Please select from the list the description that best ' .
			'describes your institution.'
		),
		array(
			'element' => & $vars['form']['field_areas_of_interest']['und']['select'],
			'desc' => 'Please select one or more areas of interest.'
		),
		array(
			'element' => & $vars['form']['picture']['picture_upload'],
			'desc' => 'This profile picture will be viewable by all registered ' .
			'users. Please select a picture to upload or select an avatar.'
		),
	);

	foreach ($elements as $element) {
		_accrualnet_hover_desc($element['element'], $element['desc']);
	}*/
}

/**
 * Moves the element's description (if any) to the #hover_desc key.
 * @param <type> $element the element to alter.
 * @param <type> $desc an overriding description, if desired.
 */
function _accrualnet_hover_desc(&$element, $desc = '') {
	if (empty($desc)) {
		// lift the existing description
		$desc = $element['#description'];
	}

	unset($element['#description']);

	$element['#hover_desc'] = $desc;
}

function accrualnet_preprocess_user_profile_form(&$vars) {
    
	try {
		hide($vars['form']['timezone']);
		hide($vars['form']['group_audience']);
$vars['form']['account']['name']['#title'] = "";
		$vars['form']['account']['name']['#description'] = 'This username will be displayed to all registered users if you participate in conversations or make comments on resources';
		$vars['form']['account']['mail']['#description'] = '';
		$vars['form']['account']['current_pass']['#description'] = '';
		$vars['form']['account']['pass']['#description'] = 'Please enter a password containing both letters and numbers.';

		$vars['form']['account']['pass']['pass1']['#title'] = 'New Password';
		$vars['form']['account']['pass']['pass2']['#title'] = 'Re-Type New Password';

		$vars['form']['picture']['#title'] = '';
		hide($vars['form']['picture']['picture_delete']);
                
                $vars['form']['profile_color']['und']['#description'] = '';

		$vars['form']['picture']['picture_upload']['#size'] = 0;
		$vars['form']['picture']['picture_upload']['#description'] =
				"You can upload a JPG, GIF, or PNG file.\n(File size limit is 2MB)";
		$vars['form']['picture']['picture_upload']['#title'] = 'Upload Photo';
		//$vars['form']['picture']['select_avatar']['#title'] = 'Or Select an Avatar';

		//$vars['form']['picture']['#attached']['js'] = array(
		//	drupal_get_path('theme', 'accrualnet') . '/js/photo_crop.js',
		//);
		//print kprint_r($vars, TRUE, '$vars');
	} catch (Exception $e) {
		print_r($e->getMessage());
	}

}

function accrualnet_form_element_label($variables) {
    
	$element = $variables['element'];
	// This is also used in the installer, pre-database setup.
	$t = get_t();

	// If title and required marker are both empty, output no label.
	if ((!isset($element['#title']) || $element['#title'] === '') && empty($element['#required'])) {
		return '';
	}

	// If the element is required, a required marker is appended to the label.
	$required = !empty($element['#required']) ? theme('form_required_marker', array('element' => $element)) : '';

	$title = filter_xss_admin($element['#title']);

	$attributes = array();
	// Style the label as class option to display inline with the element.
	if ($element['#title_display'] == 'after') {
		$attributes['class'] = 'option';
	}
	// Show label only to screen readers to avoid disruption in visual flows.
	elseif ($element['#title_display'] == 'invisible') {
		$attributes['class'] = 'element-invisible';
	}

	if (!empty($element['#id'])) {
		$attributes['for'] = $element['#id'];
	}

	// calculate the description element prior to building the label
	$desc = '';
	if (!empty($element['#hover_desc'])) {
		//$desc = '<div class="description">' . $element['#description'] . "</div>\n";
		$desc = ' <img src="/sites/accrualnet.cancer.gov/themes/accrualnet/tooltip.png" title="' . $element['#hover_desc'] . '">';
	}

	// string describing the label format
	$format = '!title !required !desc';

	// move the required field if desc exists
	if (!empty($desc))
		$format = '!required !title !desc';

	// The leading whitespace helps visually separate fields from inline labels.
	return ' <label' . drupal_attributes($attributes) . '>' . $t($format, array('!title' => $title, '!required' => $required, '!desc' => $desc)) . "</label>\n";
}

function accrualnet_preprocess_search_results(&$variables) {
    // define the number of results being shown on a page
    $itemsPerPage = 10;

    $searchTerm = $_REQUEST['q'];
    $searchTerm = ltrim(substr($searchTerm, strrpos($searchTerm, '/')), '/');

    global $pager_total_items;
    if ($pager_total_items != null) {
        // get the total number of results from the $GLOBALS
        $total = $pager_total_items[0];
    } else {
        $total = 0;
    }



    // set this html to the $variables
    if ($total > 1 || $total == 0) {
        $variables['search_totals'] = "\"$searchTerm\" gave $total results";
    } else {
        $variables['search_totals'] = "\"$searchTerm\" gave $total result";
    }

}

// Added By Lauren July 19, 2012
function accrualnet_form_alter(&$form, &$form_state, $form_id) {
    // Added by Lauren July 19, 2012
    // TIR #1823
    if ($form_id == 'search_form') {
        // Remove the ability to have an advanced search
        unset($form['advanced']);
        // Remove the "Enter your keywords" label for the search
        unset($form['basic']['keys']['#title']);
    }
    
}

function accrualnet_preprocess_search_result(&$vars) {
	//print kprint_r($vars, true, 'search result');
}

/* function accrualnet_search_page($results) {
  print kpr($results, true, 'search page');

  $output['prefix']['#markup'] = '<ol class="search-results">';

  foreach ($results as $entry) {
  $output[] = array(
  '#theme' => 'search_result',
  '#result' => $entry,
  '#module' => 'my_module_name',
  );
  }
  $output['suffix']['#markup'] = '</ol>' . theme('pager');

  return $output;
  } */

/**
 * Return a themed breadcrumb trail.
 *
 * @param $variables
 *   - title: An optional string to be used as a navigational heading to give
 *     context for breadcrumb links to screen-reader users.
 *   - title_attributes_array: Array of HTML attributes for the title. It is
 *     flattened into a string within the theme function.
 *   - breadcrumb: An array containing the breadcrumb links.
 * @return
 *   A string containing the breadcrumb output.
 */
function accrualnet_breadcrumb($variables) {
	$breadcrumb = $variables['breadcrumb'];
	$output = '';
        if(empty($breadcrumb)){
            $breadcrumb[0] = '<a href="/">Home</a>';
        }
	// Determine if we are to display the breadcrumb.
	$show_breadcrumb = theme_get_setting('accrualnet_breadcrumb');
	if ($show_breadcrumb == 'yes' || $show_breadcrumb == 'admin' && arg(0) == 'admin') {

		// Optionally get rid of the homepage link.
		$show_breadcrumb_home = theme_get_setting('accrualnet_breadcrumb_home');
		if (!$show_breadcrumb_home) {
			array_shift($breadcrumb);
		}

		// Return the breadcrumb with separators.
		if (!empty($breadcrumb)) {
			$breadcrumb_separator = theme_get_setting('accrualnet_breadcrumb_separator');
			$trailing_separator = $title = '';
			if (theme_get_setting('accrualnet_breadcrumb_title')) {
				$item = menu_get_item();
				if (!empty($item['tab_parent'])) {
					// If we are on a non-default tab, use the tab's title.
					$breadcrumb[] = check_plain($item['title']);
				} else {
					$breadcrumb[] = drupal_get_title();
				}
			} elseif (theme_get_setting('accrualnet_breadcrumb_trailing')) {
				$trailing_separator = $breadcrumb_separator;
			}

			// Provide a navigational heading to give context for breadcrumb links to
			// screen-reader users.
			if (empty($variables['title'])) {
				$variables['title'] = t('You are here');
			}
			// Unless overridden by a preprocess function, make the heading invisible.
			if (!isset($variables['title_attributes_array']['class'])) {
				$variables['title_attributes_array']['class'][] = 'element-invisible';
			}

			// Build the breadcrumb trail.
			$output = '<nav class="breadcrumb" role="navigation">';
			$output .= '<h2' . drupal_attributes($variables['title_attributes_array']) . '>' . $variables['title'] . '</h2>';
			$output .= '<ol><li>' . implode($breadcrumb_separator . '</li><li>', $breadcrumb) . $trailing_separator . '</li></ol>';
			$output .= '</nav>';
		}
	}

	return $output;
}

/**
 * Override or insert variables into the html template.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered. This is usually "html", but can
 *   also be "maintenance_page" since accrualnet_preprocess_maintenance_page() calls
 *   this function to have consistent variables.
 */
function accrualnet_preprocess_html(&$variables, $hook) {
	// Add variables and paths needed for HTML5 and responsive support.
	$variables['base_path'] = base_path();
	$variables['path_to_accrualnet'] = drupal_get_path('theme', 'accrualnet');
	$html5_respond_meta = theme_get_setting('accrualnet_html5_respond_meta');
	$variables['add_respond_js'] = in_array('respond', $html5_respond_meta);
	$variables['add_html5_shim'] = in_array('html5', $html5_respond_meta);
	$variables['default_mobile_metatags'] = in_array('meta', $html5_respond_meta);

	// If the user is silly and enables accrualnet as the theme, add some styles.
	if ($GLOBALS['theme'] == 'accrualnet') {
		include_once './' . $variables['path_to_accrualnet'] . '/accrualnet-internals/template.accrualnet.inc';
		_accrualnet_preprocess_html($variables, $hook);
	}

	// Attributes for html element.
	$variables['html_attributes_array'] = array(
		'lang' => $variables['language']->language,
		'dir' => $variables['language']->dir,
	);

	// Send X-UA-Compatible HTTP header to force IE to use the most recent
	// rendering engine or use Chrome's frame rendering engine if available.
	// This also prevents the IE compatibility mode button to appear when using
	// conditional classes on the html tag.
	if (is_null(drupal_get_http_header('X-UA-Compatible'))) {
		drupal_add_http_header('X-UA-Compatible', 'IE=edge,chrome=1');
	}

	$variables['skip_link_anchor'] = theme_get_setting('accrualnet_skip_link_anchor');
	$variables['skip_link_text'] = theme_get_setting('accrualnet_skip_link_text');

	// Return early, so the maintenance page does not call any of the code below.
	if ($hook != 'html') {
		return;
	}

	// Classes for body element. Allows advanced theming based on context
	// (home page, node of certain type, etc.)
	if (!$variables['is_front']) {
		// Add unique class for each page.
		$path = drupal_get_path_alias($_GET['q']);
		// Add unique class for each website section.
		list($section, ) = explode('/', $path, 2);
		$arg = explode('/', $_GET['q']);
		if ($arg[0] == 'node' && isset($arg[1])) {
			if ($arg[1] == 'add') {
				$section = 'node-add';
			} elseif (isset($arg[2]) && is_numeric($arg[1]) && ($arg[2] == 'edit' || $arg[2] == 'delete')) {
				$section = 'node-' . $arg[2];
			}
		}
		$variables['classes_array'][] = drupal_html_class('section-' . $section);
	}
	if (theme_get_setting('accrualnet_wireframes')) {
		$variables['classes_array'][] = 'with-wireframes'; // Optionally add the wireframes style.
	}
	// Store the menu item since it has some useful information.
	$variables['menu_item'] = menu_get_item();
	if ($variables) {
		//ADDED by Doyle to add menu class to body tag
		$item = menu_get_active_trail();
		if (count($item) > 1 &&
				// ADDED by Dan to catch missing 'link_title' key
				isset($item[1]['link_title'])) {
			$navTitle = $item[1]['link_title'];
			$variables['classes_array'][] = drupal_html_class('nav-section-' . $navTitle);
		}

		//End Added by Doyle
		switch ($variables['menu_item']['page_callback']) {
			case 'views_page':
				// Is this a Views page?
				$variables['classes_array'][] = 'page-views';
				break;
			case 'page_manager_page_execute':
			case 'page_manager_node_view':
			case 'page_manager_contact_site':
				// Is this a Panels page?
				$variables['classes_array'][] = 'page-panels';
				break;
		}
	}
}

/**
 * Override or insert variables into the html templates.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("html" in this case.)
 */
function accrualnet_process_html(&$variables, $hook) {
	// Flatten out html_attributes.
	$variables['html_attributes'] = drupal_attributes($variables['html_attributes_array']);
}

/**
 * Override or insert variables in the html_tag theme function.
 */
function accrualnet_process_html_tag(&$variables) {
	$tag = &$variables['element'];

	if ($tag['#tag'] == 'style' || $tag['#tag'] == 'script') {
		// Remove redundant type attribute and CDATA comments.
		unset($tag['#attributes']['type'], $tag['#value_prefix'], $tag['#value_suffix']);

		// Remove media="all" but leave others unaffected.
		if (isset($tag['#attributes']['media']) && $tag['#attributes']['media'] === 'all') {
			unset($tag['#attributes']['media']);
		}
	}
}

/**
 * Implement hook_html_head_alter().
 */
function accrualnet_html_head_alter(&$head) {
	// Simplify the meta tag for character encoding.
	if (isset($head['system_meta_content_type']['#attributes']['content'])) {
		$head['system_meta_content_type']['#attributes'] = array('charset' => str_replace('text/html; charset=', '', $head['system_meta_content_type']['#attributes']['content']));
	}
}

/**
 * Override or insert variables into the page template.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("page" in this case.)
 */
function accrualnet_preprocess_page(&$variables, $hook) {
	// Find the title of the menu used by the secondary links.
	$secondary_links = variable_get('menu_secondary_links_source', 'user-menu');
	if ($secondary_links) {
		$menus = function_exists('menu_get_menus') ? menu_get_menus() : menu_list_system_menus();
		$variables['secondary_menu_heading'] = $menus[$secondary_links];
	} else {
		$variables['secondary_menu_heading'] = '';
	}
}

/**
 * Override or insert variables into the maintenance page template.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("maintenance_page" in this case.)
 */
function accrualnet_preprocess_maintenance_page(&$variables, $hook) {
	accrualnet_preprocess_html($variables, $hook);
	// There's nothing maintenance-related in accrualnet_preprocess_page(). Yet.
	//accrualnet_preprocess_page($variables, $hook);
}

/**
 * Override or insert variables into the maintenance page template.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("maintenance_page" in this case.)
 */
function accrualnet_process_maintenance_page(&$variables, $hook) {
	accrualnet_process_html($variables, $hook);
	// Ensure default regions get a variable. Theme authors often forget to remove
	// a deleted region's variable in maintenance-page.tpl.
	foreach (array('header', 'navigation', 'highlighted', 'help', 'content', 'sidebar_first', 'sidebar_second', 'footer', 'bottom') as $region) {
		if (!isset($variables[$region])) {
			$variables[$region] = '';
		}
	}
}

/**
 * Override or insert variables into the node templates.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("node" in this case.)
 */
function accrualnet_preprocess_node(&$variables, $hook) {
	// Add $unpublished variable.
	$variables['unpublished'] = (!$variables['status']) ? TRUE : FALSE;

	// Add pubdate to submitted variable.
	$variables['pubdate'] = '<time pubdate datetime="' . format_date($variables['node']->created, 'custom', 'c') . '">' . $variables['date'] . '</time>';
	if ($variables['display_submitted']) {
		$variables['submitted'] = t('Submitted by !username on !datetime', array('!username' => $variables['name'], '!datetime' => $variables['pubdate']));
	}

	// Add a class for the view mode.
	if (!$variables['teaser']) {
		$variables['classes_array'][] = 'view-mode-' . $variables['view_mode'];
	}

	// Add a class to show node is authored by current user.
	if ($variables['uid'] && $variables['uid'] == $GLOBALS['user']->uid) {
		$variables['classes_array'][] = 'node-by-viewer';
	}

	$variables['title_attributes_array']['class'][] = 'node-title';
}

/**
 * Override or insert variables into the comment templates.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("comment" in this case.)
 */
function accrualnet_preprocess_comment(&$variables, $hook) {
	// If comment subjects are disabled, don't display them.
	if (variable_get('comment_subject_field_' . $variables['node']->type, 1) == 0) {
		$variables['title'] = '';
	}

	// Add pubdate to submitted variable.
	$variables['pubdate'] = '<time pubdate datetime="' . format_date($variables['comment']->created, 'custom', 'c') . '">' . $variables['created'] . '</time>';
	$variables['submitted'] = t('!username replied on !datetime', array('!username' => $variables['author'], '!datetime' => $variables['pubdate']));

	// Zebra striping.
	if ($variables['id'] == 1) {
		$variables['classes_array'][] = 'first';
	}
	if ($variables['id'] == $variables['node']->comment_count) {
		$variables['classes_array'][] = 'last';
	}
	$variables['classes_array'][] = $variables['zebra'];

	$variables['title_attributes_array']['class'][] = 'comment-title';
}


/**
 * Preprocess variables for region.tpl.php
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("region" in this case.)
 */
function accrualnet_preprocess_region(&$variables, $hook) {
	// Sidebar regions get some extra classes and a common template suggestion.
	if (strpos($variables['region'], 'sidebar_') === 0) {
		$variables['classes_array'][] = 'column';
		$variables['classes_array'][] = 'sidebar';
		// Allow a region-specific template to override accrualnet's region--sidebar.
		array_unshift($variables['theme_hook_suggestions'], 'region__sidebar');
	}
	// Use a template with no wrapper for the content region.
	elseif ($variables['region'] == 'content') {
		// Allow a region-specific template to override accrualnet's region--no-wrapper.
		array_unshift($variables['theme_hook_suggestions'], 'region__no_wrapper');
	}
}

/**
 * Override or insert variables into the block templates.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("block" in this case.)
 */
function accrualnet_preprocess_block(&$variables, $hook) {
	// Use a template with no wrapper for the page's main content.
	if ($variables['block_html_id'] == 'block-system-main') {
		$variables['theme_hook_suggestions'][] = 'block__no_wrapper';
	}

	// Classes describing the position of the block within the region.
	if ($variables['block_id'] == 1) {
		$variables['classes_array'][] = 'first';
	}
	// The last_in_region property is set in accrualnet_page_alter().
	if (isset($variables['block']->last_in_region)) {
		$variables['classes_array'][] = 'last';
	}
	$variables['classes_array'][] = $variables['block_zebra'];

	$variables['title_attributes_array']['class'][] = 'block-title';

	// Add Aria Roles via attributes.
	switch ($variables['block']->module) {
		case 'system':
			switch ($variables['block']->delta) {
				case 'main':
					// Note: the "main" role goes in the page.tpl, not here.
					break;
				case 'help':
				case 'powered-by':
					$variables['attributes_array']['role'] = 'complementary';
					break;
				default:
					// Any other "system" block is a menu block.
					$variables['attributes_array']['role'] = 'navigation';
					break;
			}
			break;
		case 'menu':
		case 'menu_block':
		case 'blog':
		case 'book':
		case 'comment':
		case 'forum':
		case 'shortcut':
		case 'statistics':
			$variables['attributes_array']['role'] = 'navigation';
			break;
		case 'search':
			$variables['attributes_array']['role'] = 'search';
			break;
		case 'help':
		case 'aggregator':
		case 'locale':
		case 'poll':
		case 'profile':
			$variables['attributes_array']['role'] = 'complementary';
			break;
		case 'node':
			switch ($variables['block']->delta) {
				case 'syndicate':
					$variables['attributes_array']['role'] = 'complementary';
					break;
				case 'recent':
					$variables['attributes_array']['role'] = 'navigation';
					break;
			}
			break;
		case 'user':
			switch ($variables['block']->delta) {
				case 'login':
					$variables['attributes_array']['role'] = 'form';
					break;
				case 'new':
				case 'online':
					$variables['attributes_array']['role'] = 'complementary';
					break;
			}
			break;
	}
}

/**
 * Override or insert variables into the block templates.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("block" in this case.)
 */
function accrualnet_process_block(&$variables, $hook) {
	// Drupal 7 should use a $title variable instead of $block->subject.
	$variables['title'] = $variables['block']->subject;
}

/**
 * Implements hook_page_alter().
 *
 * Look for the last block in the region. This is impossible to determine from
 * within a preprocess_block function.
 *
 * @param $page
 *   Nested array of renderable elements that make up the page.
 */
function accrualnet_page_alter(&$page) {
	// Look in each visible region for blocks.
	foreach (system_region_list($GLOBALS['theme'], REGIONS_VISIBLE) as $region => $name) {
		if (!empty($page[$region])) {
			// Find the last block in the region.
			$blocks = array_reverse(element_children($page[$region]));
			while ($blocks && !isset($page[$region][$blocks[0]]['#block'])) {
				array_shift($blocks);
			}
			if ($blocks) {
				$page[$region][$blocks[0]]['#block']->last_in_region = TRUE;
			}
		}
	}
}

/**
 * Implements hook_form_BASE_FORM_ID_alter().
 *
 * Prevent user-facing field styling from screwing up node edit forms by
 * renaming the classes on the node edit form's field wrappers.
 */
function accrualnet_form_node_form_alter(&$form, &$form_state, $form_id) {
	// Remove if #1245218 is backported to D7 core.
	foreach (array_keys($form) as $item) {
		if (strpos($item, 'field_') === 0) {
			if (!empty($form[$item]['#attributes']['class'])) {
				foreach ($form[$item]['#attributes']['class'] as &$class) {
					if (strpos($class, 'field-type-') === 0 || strpos($class, 'field-name-') === 0) {
						// Make the class different from that used in theme_field().
						$class = 'form-' . $class;
					}
				}
			}
		}
	}
}
