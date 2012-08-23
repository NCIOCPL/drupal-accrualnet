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
module_load_include('inc', 'resource', 'includes/types');
global $an_resource_types;
?>
<?php if (!in_array($type, array_keys($an_resource_types))): ?>
    <article class="node-<?php print $node->nid; ?> <?php print $classes; ?> clearfix"<?php print $attributes; ?>>

    <?php if ($title_prefix || $title_suffix || $display_submitted || $unpublished || !$page && $title): ?>
            <header>
            <?php print render($title_prefix); ?>
            <?php if (!$page && $title): ?>
                    <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
                <?php endif; ?>
                <?php print render($title_suffix); ?>

                <?php if ($display_submitted): ?>
                    <p class="submitted">
                    <?php print $user_picture; ?>
                    <?php print $submitted; ?>
                    </p>
                    <?php endif; ?>

                <?php if ($unpublished): ?>
                    <p class="unpublished"><?php print t('Unpublished'); ?></p>
                <?php endif; ?>
            </header>
            <?php endif; ?>

        <?php
        // We hide the comments and links now so that we can render them later.
        hide($content['comments']);
        hide($content['links']);
        print render($content);
        ?>

        <?php print render($content['links']); ?>

        <?php print render($content['comments']); ?>

    </article><!-- /.node -->
    <?php else: ?>
    <?php
// Module Global Variables
    module_load_include('module', 'resource');
    global $an_resource_field_citation;
    global $an_resource_citation_fields_A, $an_resource_citation_fields_B, $an_resource_citation_fields_C;
    global $an_resource_field_resource;
    global $an_vocabularies;
    ?>
    <div class="resource-content <?php print $type; ?>">
    <?php
    $citationOutput = _resource_output_citation($node);
    $taxonomyOutput = _resource_output_taxonomy($node);







// Related Links
    
    $linksOutput = '<div id="resource-links">';
    if (count($field_links) > 0) {
    $linksOutput .= '<h3>Links</h3>';
    $linksOutput .= '<ul>';
    foreach ($field_links as $link) {
        $linksOutput .= '<li>';
        $linksOutput .= '<a href="' . $link['url'] . '" target="_blank">';
        $linksOutput .= $link['title'];
        $linksOutput .= '</a>';
        $linksOutput .= '</li>';
    }
    }
    $linksOutput .= '</ul></div>';


    $fieldsToRender = $an_resource_field_resource;
    array_pop($fieldsToRender); // This should remove links


    $resourceOutput = '<div class="resource-resource">';
    foreach ($fieldsToRender as $rfield) {
        // Make sure the field returns a result
        if (isset(${"field_" . $rfield["field_name"]})) {
            // Make sure that result is of value
            if (array_key_exists('value', ${"field_" . $rfield["field_name"]}[0])) {
            if (strlen(${"field_" . $rfield["field_name"]}[0]["value"]) > 0) {

                $rfieldOutput = '<div id="resource-' . $rfield["field_name"] . '">';
                // Get name of instance, not field (different for different resources)
                $rInstance = field_read_instance('node', 'field_' . $rfield["field_name"], $type);
                $rfieldOutput .= '<h3>' . $rInstance["label"] . '</h3>';
                foreach (${"field_" . $rfield["field_name"]} as $instance) {
                    $rfieldOutput .= $instance['safe_value'];
                }
                $rfieldOutput .= '</div>';
                $resourceOutput .= $rfieldOutput;
            }
            } elseif (array_key_exists('filename', ${"field_" . $rfield["field_name"]}[0])) {
                $rfieldOutput = '<div class="resource-file" id="resource-' . $rfield["field_name"]. '">';
                if (${"field_" . $rfield["field_name"]}[0]['display'] == 1 && ${"field_" . $rfield["field_name"]}[0]['status'] == 1) {
                $rfieldOutput .= '<h3>Download Attachment:</h3> ';
                $rfieldOutput .= ' <a href="'.file_create_url(${"field_" . $rfield["field_name"]}[0]['uri']).'">';
                $rfieldOutput .= ${"field_" . $rfield["field_name"]}[0]['filename'] . '</a>';
                $rfieldOutput .= '</div>';
                $resourceOutput .= $rfieldOutput;
                }
            }
        }
    }

    $resourceOutput .= '</div>';
    
    $resourceOutput .= '<div class="back-to-top">';
    $resourceOutput .= '<a href="#top">Back to Top</a>';
    $resourceOutput .= '</div>';

// Comments
    $commentsOutput = '<div id="resource-comments">';
    $commentsOutput .= render($elements['comments']);
    $commentsOutput .= '</div>';


// Build the page
    print $citationOutput;
    print $taxonomyOutput;
    print $linksOutput;
    print $resourceOutput;
    print $commentsOutput;
    ?>
    </div>
    <?php endif; ?>
