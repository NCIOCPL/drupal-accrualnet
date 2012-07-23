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
<?php if ($search_results): ?>
	<h2 class="search-title"><?php print t('SITE WIDE SEARCH RESULTS'); ?></h2>
	<hr class="search-divider" />
	<div class="search-pager"><?php print $pager; ?></div>
	<div class="search-count"><?php print strtoupper($search_totals); ?></div>
	<ol class="search-results <?php print $module; ?>-results">
		<?php print $search_results; ?>
	</ol>
	<div class="search-pager"><?php print $pager; ?></div>
<?php else : ?>
	<h2><?php print $search_totals; ?></h2>
	<?php print search_help('search#noresults', drupal_help_arg()); ?>
<?php endif; ?>
