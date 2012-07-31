<?php
/**
 * @file
 * Default theme implementation for displaying search results.
 *
 * This template collects each invocation of theme_search_result(). This and
 * the child template are dependent to one another sharing the markup for
 * definition lists.
 *
 * Note that modules may implement their own search type and theme function
 * completely bypassing this template.
 *
 * Available variables:
 * - $search_results: All results as it is rendered through
 *   search-result.tpl.php
 * - $module: The machine-readable name of the module (tab) being searched, such
 *   as "node" or "user".
 *
 *
 * @see template_preprocess_search_results()
 */
?>
<div id="search-header">
    <div id="search-count"><?php print strtoupper($search_totals); ?></div>
    <?php if ($pager): ?>
    <div class="pager top-pager search-pager"><?php print $pager; ?></div>
    <?php endif; ?>
</div>

<ol class="search-results <?php print $module; ?>-results">
<?php if ($search_results) {
print $search_results; 
} else {
	print search_help('search#noresults', drupal_help_arg());
}
?>
</ol>
    <?php if ($pager): ?>
    <div class="pager bottom-pager search-pager"><?php print $pager; ?></div>
    <?php endif; ?>