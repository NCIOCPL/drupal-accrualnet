<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

$gid = $group_group['und'][0]['value'];
//print kprint_r(get_defined_vars());
/*
$query = new EntityFieldQuery();
$query->entityCondition('entity_type', 'og_membership')
        ->propertyCondition('gid', $gid)
        ->propertyCondition('entity_type', 'node');
$result = $query->execute();

print kprint_r($result["og_membership"]);

$eload = entity_load_single('og_membership', $gid);

print kprint_r('test');
print kprint_r($eload);
print kprint_r(entity_get_info('og_membership'));

$convos = array();
foreach (array_keys($result['og_membership']) as $convo) {
    print $convo;
    $convos[] = node_load($convo);
}
print kprint_r($convos);
 * 
 */

$query = db_query("SELECT etid FROM {og_membership} WHERE gid=".$gid." AND entity_type='node'");
$convos = array();
foreach ($query as $result) {
    $convos[] = node_load($result->etid);
}
//print kprint_r($convos);
?>
<?php if ($body) print $body[0]['safe_value']; ?>
<?php
$o = '';
foreach ($convos as $convo) {
    $o .= '<div class="conversation-result">';
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
    $bodyContent = $convo->body['und'][0]['value'];
    $bodyTilPeriod = substr($bodyContent, 0, strpos($bodyContent, '.')+1);
    $o .= $bodyTilPeriod;
    $o .= '</div>';
    
    $o .= '<div class="conversation-starter">';
    $o .= 'Started by: ';
    $o .= '<a href="'. url('user/' . $node->uid). '">';
    $o .= user_load($node->uid)->name;
    $o .= '</a>';
    $o .= '</div>';
    
    $comment = comment_get_thread($convo, COMMENT_MODE_FLAT, 1);
    if ($comment != NULL) {
        $comment = comment_load($comment[0]);
        $commenter = user_load($comment->uid);
    $o .= '<div class="conversation-recent">';
    $o .= '<div class="conversation-recent-text">';
    $o .= 'Recent Activity:';
    $o .= '</div>';
    $o .= '<div class="conversation-recent-comment">';
    /* NOT IMPLEMENTED
    $o .= '<div class="conversation-recent-comment-userpic">';
    $o .= '<img/>';
    $o .= '</div>';*/
    $o .= '<div class="conversation-recent-comment-text">';
    $o .= '<a href="'.url('user/' . $commenter->uid).'">'.$commenter->name.'</a>';
    $o .= '<br/>';
    $o .= $comment->comment_body['und'][0]['safe_value'];
    $o .= '</div>';
    $o .= '</div>';
    $o .= '</div>';
    }
    $o .= '</div>'; // Ends paritcular convo
}

print $o;
?>