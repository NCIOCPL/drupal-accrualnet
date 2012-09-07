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
 *  <?php if($summary): ?>
        <div class="convo-summary">
            <?php print $summary[0]['value'];?>
        </div>
    <?php endif;?>
 * 
 <?php if($body): ?>
        <div class="convo-post convo-post even">
        <div class="convo-user-image">
                <?php print theme('image_style',
                    array(
                        'path' => $user->picture->uri,
                        'style_name' => 'thumbnail',         
                    )
                ); ?>
         </div>
            <div class="convo-body">
            <div class="submitted-by">
                <span class="user-name">
                    <a href="/user/<?php print $node->uid;?>" class="<?php print $nci_user_profile_colors[$color[0]['value']];?>" title="<?php print $user->name;?>'s profile"><?php print $user->name;?></a>
                </span>
                <span class="user-occupation"><?php print check_plain($occupation[0]['value']);?></span>
                <span class="posted-date"><?php print format_date($node->created, 'custom', 'F d, Y');?></span>
            </div>
            <?php print $body[0]['value'];?>
        </div>
            
    </div>
    <?php endif;?>
        <?php print render($content['comments']);?>
    </div>
    
</div>

 * 
 * @see template_preprocess()
 * @see template_preprocess_node()
 * @see zen_preprocess_node()
 * @see template_process()
 */






global $nci_user_profile_colors;
$topic = field_get_items('node', $node, 'field_topic');




$term =  taxonomy_term_load($topic[0]['tid']);

//$summary = field_get_items('node', $node, 'field_conversation_summary');
//$body = field_get_items('node', $node, 'body');
$opener = field_get_items('node', $node, 'field_conversation_opener', array('label' => 'hidden'));


$title = '';
$user = user_load($node->uid);
$occupation = field_get_items('user', $user, 'field_occupation');
$color = field_get_items('user', $user, 'profile_color');
$avatar = field_get_items('user', $user, 'avatar_image');

if ($avatar) {
    $simulatedAvatarArray = array();
    foreach ($nci_user_profile_colors as $avatarColor) {
        $simulatedAvatarArray[] = 'male/'.$avatarColor;
        $simulatedAvatarArray[] = 'female/'.$avatarColor;
    }
    $avatarTMP = intval($avatar[0]['value']);
    $avatarTMP = $simulatedAvatarArray[$avatarTMP];
    $avatarSRC = '/' . path_to_theme() . '/accrualnet-internals/images/avatars/' . $avatarTMP . '.png';
}
else {
    $avatarSRC = '/' . path_to_theme() . '/accrualnet-internals/images/avatars/male/Black.png';

}
$op = field_get_items('node', $node, 'op');
//$comments = comment_get_thread($node,COMMENT_MODE_FLAT, 10  );
?>

<?php if($op == "Preview"): //Certain items break on preview because they dont exist, strip them out so a user can still use preview.?>
    <div class="conversation-topic-header">
        <?php print _communities_convo_header($node, $term);?>
    </div>
    <div class="conversation">
        <div class="convo-title">
            <h2>
            <?php print check_plain($node->title);?>            
            </h2>
        </div>
        <div class="conversation-abstract">
            <?php if ($body) print drupal_render(field_view_field('node', $node, 'body', array('label' => 'hidden'))); ?>
            <?php print drupal_render(field_view_field('node', $node, 'field_file_attachment', array('label' => 'hidden')));?>
        </div>

        <div class="convo-posts">
        <?php if($opener): ?>

            <div class="convo-post convo-post even">
            <div class="convo-user-image">
                <?php if($user->picture):?>
                    <?php print theme('image_style',
                            array(
                                'path' => $user->picture->uri,
                                'style_name' => 'thumbnail',    
                                'alt' => $user->name ."'s Image",
                            )
                        ); ?>
                <?php else: ?>
                    <img alt="<?php print check_plain($user->name);?>'s Image" src="<?php print $avatarSRC;?>" width="100" title="<?php print check_plain($user->name);?>'s Image" alt="<?php print check_plain($user->name);?>'s Image" />

                <?php endif;?>

            </div>
                <div class="convo-body">
                <div class="submitted-by">
                    <span class="user-name">
                        <a href="/user/<?php print $node->uid;?>" class="<?php print $color ? $nci_user_profile_colors[$color[0]['value']] : 'Black';?>" title="<?php print $user->name;?>'s profile"><?php print $user->name;?></a>
                    </span>
                    <span class="user-occupation"><?php print check_plain($occupation[0]['value']);?></span>
                    <span class="posted-date"><?php print format_date($node->created, 'custom', 'F d, Y');?></span>
                </div>
                <?php print $opener[0]['safe_value']; ?>
            </div>

        </div>
        <?php endif;?>
            <?php if(user_is_logged_in()):?>
            <?php print render($content['comments']);?>
            <?php else: ?>
            <div class="comment-cta">
                <p>Please <a href="/user" title="login" alt="login">Login</a> or <a href="/user/register" title="register" alt="register">Register</a> to post comments.</p>
            </div>
            <?php endif;?>
        </div>

    </div>
<?php else:?>
    <div class="conversation-topic-header">
        <?php print _communities_convo_header($node, $term);?>
    </div>
    <div class="conversation">
        <div class="convo-title">
            <h2>
            <?php print check_plain($node->title);?>

            
            </h2>
            <div class="last-updated-snippet">
            <?php print _last_updated_snippet($node->last_comment_timestamp); ?>
            </div>
        </div>
        <div class="conversation-abstract">
            <?php if ($body) print drupal_render(field_view_field('node', $node, 'body', array('label' => 'hidden'))); ?>
        <?php print drupal_render(field_view_field('node', $node, 'field_file_attachment', array('label' => 'hidden')));?>
        
        </div>

        <div class="convo-posts">
        <?php if($opener): ?>

            <div class="convo-post convo-post even">
            <div class="convo-user-image">
                <?php if($user->picture && !$avatar):?>
                    <?php print theme('image_style',
                            array(
                                'path' => $user->picture->uri,
                                'style_name' => 'thumbnail', 
                                'alt' => $user->name ."'s Image",
                            )
                        ); ?>
                <?php else: ?>
                    <img alt="<?php print check_plain($user->name);?>'s Image" src="<?php print $avatarSRC;?>" width="100" title="<?php print check_plain($user->name);?>'s Image" alt="<?php print check_plain($user->name);?>'s Image" />

                <?php endif;?>

            </div>
                <div class="convo-body">
                <div class="submitted-by">
                    <span class="user-name">
                        <a href="/user/<?php print $node->uid;?>" class="<?php print $color ? $nci_user_profile_colors[$color[0]['value']] : 'Black';?>" title="<?php print $user->name;?>'s profile"><?php print $user->name;?></a>
                    </span>
<?php /*                    <span class="user-occupation"><?php print check_plain($occupation[0]['value']);?></span> */ ?>
				<?php 
					// look for moderator titles
					$moderator_titles = array();
					// if belongs to the co-moderator role
					if(array_search('AccrualNet Co-Moderator', $user->roles) !== false)
					{
						$moderator_titles[] = 'AccrualNet Co-Moderator';
					}
					// get the node group and the user roles
					$groups = og_get_entity_groups('node', $node);
					if(!empty($groups)){
						$gid = array_shift($groups);
						$rids = og_get_user_roles($gid, $user->uid, false);
						// a non-empty list can only contain the community moderator role
						if(!empty($rids)) {
							$moderator_titles[] = 'Community of Practice Moderator';
						}
					}
					if(!empty($moderator_titles)){
						$moderator_text = implode(', ', $moderator_titles);
						print "<span class='user-moderator'>$moderator_text</span>";
					}
				?>
                    <span class="posted-date"><?php print format_date($node->created, 'custom', 'F d, Y');?></span>
                </div>

                <?php print $opener[0]['safe_value']; ?>
            </div>

        </div>
        <?php endif;?>
            <?php print render($content['comments']);?>
            <?php if(!user_is_logged_in()):?>
            <div class="comment-cta">
                <p>Please <a href="/user" title="login" alt="login">Login</a> or <a href="/user/register" title="register" alt="register">Register</a> to post comments.</p>
            </div>
            <?php endif;?>
        </div>

    </div>
<?php endif;?>
