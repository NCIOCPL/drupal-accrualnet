<?php

/**
 *
 * 
 *  
 */
global $user;
$o = '';
$group = og_context();
$query = db_query("SELECT etid FROM {og_membership} WHERE gid=".$group->gid." AND entity_type='node'");
$convos = array();
foreach ($query as $result) {
    $convos[] = node_load($result->etid);
}
//print kprint_r($convos);
?>
<div id="community">
    <div class="header-paragraph">
<?php if ($body) print $body[0]['safe_value']; ?>
    </div>

<?php
$o .= '';
foreach ($convos as $convo) {
    $o .= '<div class="conversation-result';
    if ($convos[count($convos) - 1] == $convo) $o .= ' last-result';
    $o .= '">'; // Start Result
    $o .= '<div class="conversation-title">';
    $o .= '<a href="' . url('node/' . $convo->nid) . '">';
	//$output .= $node->title;
    $o .= check_plain($convo->title);
	//$output .= filter_xss($node->title);
    $o .= '</a>';
    $o .= '<span class="conversation-last-updated">';
    $o .= 'Last Updated: ';
    $o .= date('M j, Y', $convo->changed);
    $o .= '</span>';
    $o .= '</div>'; // Ends title
    
    $o .= '<div class="conversation-preview">';
    $o .= _preview_snippet($convo->body);
    $o .= '</div>';
    
    $o .= _starter_snippet($convo->uid);
    
    $o  .= _get_latest_comment($convo);
    
    $o .= '</div>'; // Ends paritcular convo
}


print $o;
?>
</div>
<?php
drupal_add_js("(function ($) {
        $(document).ready(function() {
            $('nav#block-an-navigation-left-nav').append($('div#community-members'));
        
        });
    }) (jQuery);", 'inline');
?>

    <?php
    //$query = db_query("SELECT etid FROM {og_membership} WHERE gid=".$group->gid." AND entity_type='user'");
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'og_membership')
            ->propertyCondition('gid', $group->gid)
            ->propertyCondition('entity_type', 'user', '=')
            ->propertyCondition('state', '1')
            ->pager(10);
    $results = $query->execute();
    if (count($results) > 0 && count($results['og_membership']) > 0): ?>
<div id="community-members">
    <div id="community-members-title">
        Community Members
    </div>
    <div id="community-members-list">
    <?php    
    $ogmemberships = entity_load('og_membership', array_keys($results['og_membership']));
    foreach ($ogmemberships as $ogm):
        $oguser = user_load($ogm->etid);
    ?>
        <div class="community-member">
             <div class="conversation-recent-comment-userpic">
                <?php print _user_image_snippet($oguser);?>
            </div>
            <span class="community-member-name">
                <a href="<?php print url('user/' . $oguser->uid); ?>"><?php print $oguser->name; ?></a>
            </span>
        </div>
       <?php 
    endforeach; ?>
        <div id="community-members-pager">
            <?php print theme('pager'); ?>
        </div>
<?php $userGroupRoles = og_get_user_roles($group->gid, $user->uid);?> 
        <?php if(array_key_exists(3, $userGroupRoles)):?>
        <div class="manage-members">
            <span class="button"><a href="http://localhost/group/node/<?php print $group->etid;?>/admin/people">Manage Group Members</a></span>
        </div>
        <?php endif;?>
        </div>
    <?php endif;
    ?>
    
</div>
