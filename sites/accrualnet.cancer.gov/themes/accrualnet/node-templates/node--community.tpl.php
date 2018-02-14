<?php
/**
 *
 * 
 *  
 */
global $user;

$group = og_context();

$query = db_select('node', 'n')->fields('n', array('nid', 'title', 'changed'));
$query->leftJoin('og_membership', 'ogm', 'ogm.etid=n.nid');
$query->innerJoin('node_comment_statistics', 'c', 'n.nid=c.nid');
$query->condition('n.type', 'conversation')
        ->condition('n.status', '1')
        ->condition('ogm.gid', $group->gid);
$query->orderBy('c.last_comment_timestamp', 'DESC');
$query = $query->extend('PagerDefault')
        ->limit(10);

$convos = $query->execute()->fetchAllAssoc('nid');
$convosUnloaded = array_values($convos);
?>
<div id="community">
    <div class="header-paragraph">
        <?php if ($body)
            print $body[0]['safe_value']; ?>
    </div>
    <div class="community-buttons">
        <div class="start-a-convo">
            <span class="button"><a href="/node/add/conversation" title="Start a Conversation">Start a Conversation</a></span>
        </div>
        <?php
        $userGroupRoles = og_get_user_roles($group->gid, $user->uid);
        if (array_key_exists(3, $userGroupRoles) || in_array('administrator', $user->roles) || in_array('accrualnet_staff', $user->roles)):
            ?>
            <div class="manage-members">
                <span class="button"><a href="/group/node/'.$group->etid.'/admin/people">Manage Group Members</a></span>
            </div>
            <?php
        endif;
        ?>
    </div>
    <h2>Conversations</h2>
    <?php
    foreach ($convos as $convoUnloaded):
        $convo = node_load($convoUnloaded->nid);
        ?>
        <div class="conversation-result<?php if ($convosUnloaded[count($convos) - 1] == $convoUnloaded)
        print ' last-result'; ?>">

            <div class="conversation-title">
                <a href="<?php print url('node/' . $convo->nid); ?>">
                    <?php print check_plain($convo->title); ?>
                </a>

                <span class="conversation-last-updated">
                    Last Updated: <?php print date('M j, Y', $convo->last_comment_timestamp); ?>
                </span>
            </div>

            <div class="conversation-preview">
                <?php print _preview_snippet($convo->body); ?>
            </div>

            <?php
            print _starter_snippet($convo->uid);

            print _get_latest_comment($convo);
            ?>
        </div>
    <?php endforeach; ?>
    <div style="clear:both">
        <?php print theme('pager', array('tags' => array())); ?>
    </div>

</div>
<?php
drupal_add_js("(function ($) {
        $(document).ready(function() {
            $('section.region-sidebar-first nav:first-child').append($('div#community-members'));
        
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
if (count($results) > 0 && count($results['og_membership']) > 0):
    ?>
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
                        <?php print _user_image_snippet($oguser); ?>
                    </div>
                    <span class="community-member-name">
                        <a href="<?php print url('user/' . $oguser->uid); ?>"><?php print $oguser->name; ?></a>
                    </span>
                </div>
            <?php endforeach; ?>
            <?php if ($query->pager): ?>
                <div id="community-members-pager">
                    <?php $pager = $query->pager; ?>
                    <?php $pager['quantity'] = 1; ?>
                    <?php print theme('pager', $pager); ?>
                </div>
            <?php endif; ?>
            <?php $userGroupRoles = og_get_user_roles($group->gid, $user->uid);
            if (array_key_exists(3, $userGroupRoles) || in_array('administrator', $user->roles) || in_array('accrualnet_staff', $user->roles)): ?>
                <div class="manage-members">
                    <span class="button"><a href="/group/node/<?php print $group->etid; ?>/admin/people">Manage Group Members</a></span>
                </div>
            <?php endif; ?>
        </div>
    </div>
<?php endif; ?>


