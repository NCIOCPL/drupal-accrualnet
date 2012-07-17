<?php
/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

module_load_include('inc', 'nci_custom_user', 'includes\profilecolors');
global $nci_user_profile_colors;
kprint_r($form);
$account = $form['account'];
$color = $nci_user_profile_colors[0];
if (count($form['profile_color']['und']['#value']) > 0) {
    $color = $nci_user_profile_colors[array_pop($form['profile_color']['und']['#value'])];
}

// Form Changes
//kprint_r($form['account']);
$form['account']['status']['#access'] = FALSE;
$form['account']['roles']['#access'] = FALSE;

$form['account']['name']['#title'] = "";
$form['account']['pass']['#title_display'] = "after";
$scriptURL = path_to_theme() . '/js/script.js';
drupal_add_js($scriptURL);
$output = "";


/* drupal_add_js('Drupal.behaviors.password = function () {};', 'inline', 'header'); */
$selectedValuesOnLoad = array();
$selectedValuesFieldRole = $form['field_role']['und']['#default_value'];
foreach ($selectedValuesFieldRole as $selected) {
    if (!in_array($selected, $form['field_role']['und']['#options'])) {
        $selectedValuesOnLoad[] = "ROLE_OTHER";
    } else {
        $selectedValuesOnLoad[] = $selected;
    }
}
$selectedValuesFieldAOI = $form['field_areas_of_interest']['und']['#default_value'];
foreach ($selectedValuesFieldAOI as $selected) {
    if (!in_array($selected, $form['field_areas_of_interest']['und']['#options'])) {
        $selectedValuesOnLoad[] = "AOI_OTHER";
    } else {
        $selectedValuesOnLoad[] = $selected;
    }
}
//$selectedValuesOnLoad = array_merge($form['field_role']['und']['#default_value'], $form['field_areas_of_interest']['und']['#default_value']);
//$selectedValuesOnLoad = $form['field_role']['und']['#default_value'];
foreach ($selectedValuesOnLoad as &$value) {
    //$value = str_replace(' ', '-', $value);
}
drupal_add_js(path_to_theme() . '/js/checkbox.js', 'file');
drupal_add_js(path_to_theme() . '/js/profilecolors.js', 'file');
drupal_add_js(path_to_theme() . '/js/selectboxes.js', 'file');
drupal_add_js(path_to_theme() . '/js/inputdarken.js', 'file');
drupal_add_js(array('selectedValues' => $selectedValuesOnLoad), 'setting');


$form['actions']['submit']['#value'] = 'Save Changes';
$form['actions']['cancel']['#value'] = 'Cancel';
?>

<p>
    <?php print render($intro_text); ?>
</p>


<section class="column sidebar region profile-sidebar">
    <?php print render($form['picture']); ?>
    <img class="image" src="/<?php print path_to_theme(); ?>/accrualnet-internals/images/global/test.jpg" />
    <div class="profile-colors-wrapper">
        <?php
        print drupal_render($form['profile_color']);
        ?>
        <div class="profile-colors-container">
            <div class="profile-colors-selected" id="<?php print $color; ?>"></div>
            <div class="profile-colors-options">
                <?php
                foreach ($nci_user_profile_colors as $colorValue => $colorOpt) {
                    print '<span class="profile-colors-option" id="' . $colorOpt . '" title="' . $colorValue . '"></span>';
                }
                ?>
            </div>
        </div>
    </div>
</section>
<section class="column profile-content">
    <div class="accrualnet-user-profile-form-wrapper<?php print ' ' . $color; ?>">
        <?php
        //print drupal_render_children($form);

        $output .= drupal_render($form['account']['name']);
        $output .= drupal_render($form['account']['mail']);
        $test = drupal_render($form['account']['pass']);
        //kprint_r( $test);
        $output .= $test;

        $output .= drupal_render($form['field_role']);




        $selectOutputs = array('field_years_in_research', 'field_institution_type');
        foreach ($selectOutputs as $select) {
            $output .= drupal_render($form[$select]);
            if (count($form[$select]['und']) > 0) {
                $output .= '<div id="' . $select . '" class="selectBox">';
                $output .= '<span class="selected">';
                
                $output .= $index;
                $output .='</span><span class="selectArrow">&#9660</span>';
                $output .= '<div class="selectOptions">';

                if (array_key_exists('safe_value', $form[$select]['und']['#default_value'])) {
                    $safeValue = $form[$select]['und']['#default_value']['safe_value'];
                    if (!array_key_exists($safeValue, $form[$select]['und']['#options'])) {
                        $safeValue = "select_or_other";
                    }
                    foreach ($form[$select]['und']['#options'] as $selectOptionKey => $selectOptionValue) {
                        if ($selectOptionValue == $safeValue)
                            $class = 'selectOption selectedd';
                        else
                            $class = 'selectOption';
                        $output .= '<span class="' . $class . '" id="' . $selectOptionKey . '">' . $selectOptionValue . '</span>';
                    }
                } else {
                    $index = $form[$select]['und']['#default_value'][0];

                    foreach ($form[$select]['und']['#options'] as $selectOptionKey => $selectOptionValue) {
                        if ($selectOptionKey == $index)
                            $class = 'selectOption selectedd';
                        else
                            $class = 'selectOption';
                        $output .= '<span class="' . $class . '" id="' . $selectOptionKey . '">' . $selectOptionValue . '</span>';
                    }
                }
                if (array_key_exists('#other', $form[$select]['und'])) {
                    if ($safeValue == "select_or_other") {
                    $output .= '<span class="selectOption select_or_other selectedd">' . $form[$select]['und']['#other'] . '</span>';
                    } else {
                        $output .= '<span class="selectOption select_or_other">' . $form[$select]['und']['#other'] . '</span>';
                    }
                }
                $output .= '</div>';
                $output .= '<div class="select-spacer">&nbsp;</div>';
                $output .= '</div>';
            }
        }
        $output .= drupal_render($form['field_areas_of_interest']);

        $output .= drupal_render_children($form);




//kprint_r(form_builder($form['#form_id'], $form['account']['pass'], NULL));
//                $output .= drupal_render($form['account']);
        $output = str_replace('*', '<img src="/' . path_to_theme() . '/accrualnet-internals/images/global/test.jpg" />', $output);
        print $output
        ?>
    </div>
</section>
