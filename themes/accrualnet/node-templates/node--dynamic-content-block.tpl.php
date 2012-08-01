<?php

/**
 * @file
 * Zen theme's implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: An array of node items. Use render($content) to print them all,
 *   or print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $user_picture: The node author's picture from user-picture.tpl.php.
 * - $date: Formatted creation date. Preprocess functions can reformat it by
 *   calling format_date() with the desired parameters on the $created variable.
 * - $name: Themed username of node author output from theme_username().
 * - $node_url: Direct url of the current node.
 * - $display_submitted: Whether submission information should be displayed.
 * - $submitted: Submission information created from $name and $date during
 *   template_preprocess_node().
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - node: The current template type, i.e., "theming hook".
 *   - node-[type]: The current node type. For example, if the node is a
 *     "Blog entry" it would result in "node-blog". Note that the machine
 *     name will often be in a short form of the human readable label.
 *   - node-teaser: Nodes in teaser form.
 *   - node-preview: Nodes in preview mode.
 *   - view-mode-[mode]: The view mode, e.g. 'full', 'teaser'...
 *   The following are controlled through the node publishing options.
 *   - node-promoted: Nodes promoted to the front page.
 *   - node-sticky: Nodes ordered above other non-sticky nodes in teaser
 *     listings.
 *   - node-unpublished: Unpublished nodes visible only to administrators.
 *   The following applies only to viewers who are registered users:
 *   - node-by-viewer: Node is authored by the user currently viewing the page.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type, i.e. story, page, blog, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $pubdate: Formatted date and time for when the node was published wrapped
 *   in a HTML5 time element.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Node status variables:
 * - $view_mode: View mode, e.g. 'full', 'teaser'...
 * - $teaser: Flag for the teaser state (shortcut for $view_mode == 'teaser').
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *   main body content. Currently broken; see http://drupal.org/node/823380
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * Field variables: for each field instance attached to the node a corresponding
 * variable is defined, e.g. $node->body becomes $body. When needing to access
 * a field's raw values, developers/themers are strongly encouraged to use these
 * variables. Otherwise they will have to explicitly specify the desired field
 * language, e.g. $node->body['en'], thus overriding any language negotiation
 * rule that was previously applied.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 * @see zen_preprocess_node()
 * @see template_process()
 */



//NOTE: Assuming that there is enough content to have the number requested.
//THIS COULD FAIL IF NOT!!
//
//

//field_display_format is required
$format = field_get_items('node', $node, 'field_display_format');
//field_order_by is required
$order = field_get_items('node', $node, 'field_order_by');
//field_featured_type is required so it must be here.
$types = field_get_items('node', $node, 'field_featured_type');
//get image(if it exists)
$image = field_get_items('node', $node, 'field_featured_image');
$link = field_get_items('node', $node, 'field_more_link');


$numConvosPerPage = 10;
$query = db_select('node', 'n')->fields('n', array('nid', 'title', 'created'));
$query->leftJoin('og_membership', 'ogm', 'ogm.etid=n.nid');
if($types){
    $query->condition('n.type',  array_values($types) , 'IN');
}
$query->condition('n.status', '1')
        ->condition('ogm.gid', 'NULL', 'IS NULL');
$query->orderBy('n.created', 'DESC');
$query = $query->extend('PagerDefault')->limit($numConvosPerPage);
$content = $query->execute()->fetchAllAssoc('nid');


$featuredContent = entity_load('node', array_keys($content));




//Build out the entityFieldQuery for this content type.
$query = new EntityFieldQuery();
$query->entityCondition('entity_type', 'node')
 ->entityCondition('bundle', array_values($types))
 ->propertyCondition('status', 1);
 //Switch statement for the range
switch($format[0]['value'])
{
    case 'listing':
        $query->range(0,6);
        break;
    case 'listing_image':
        $query->range(0,3);
        break;
    default:
        //this should never be reachable.
        break;
}
 
switch($order[0]['value']){
    case 'alpha':
        $query->propertyOrderBy('title', 'ASC');
        break;
    case 'date_recent':
        $query->propertyOrderBy('created',  'DESC');
        break;
    case 'manual':
        //if manual, dont do anything, we are going to use the order they are inserted in the node.
        break;
    default:
        //this should never be reachable.
        break;
}
 

//$featuredContent = _an_lifecycle_load_related_nodes($query, TRUE);

?>
<div class="featured-content-title">
    <span class="feature-header"><?php print filter_xss($node->title);?></span>
</div>
<div class="featured-content-block">
    <?php $counter = 1;?>
    <?php foreach($featuredContent as $item):?>
        <?php if($counter == 1 || $counter == 4):?>
            <div class="featured-content-section-<?php print $counter;?>">
        <?php endif;?>
        
            <?php $urlPath = drupal_lookup_path('alias', 'node/'.$item->nid); ?>
                <?php print _featured_content_display($item, FALSE, FALSE, FALSE);?>
            
        
        <?php if($counter == 3 || $counter == 6):?>
            </div>
        <?php endif;?>
        <?php $counter++;?>
    <?php endforeach;?>
    
    <?php if($format[0]['value'] == 'listing_image'):?>
        <div class="featured-content-picture">
            <?php if($image): ?>
                <?php print theme('image_style',  array(
                                'path' => $image[0]['uri'],
                                'style_name' => 'large',         
                            )
                        );?>
            <?php endif;?>
        </div>
    <?php endif;?>
</div>