<?php
/**
 * @file
 * Default theme implementation to present a picture configured for the
 * user's account.
 *
 * Available variables:
 * - $user_picture: Image set by the user or the site's default. Will be linked
 *   depending on the viewer's permission to view the user's profile page.
 * - $account: Array of account information. Potentially unsafe. Be sure to
 *   check_plain() before use.
 *
 * @see template_preprocess_user_picture()
 */
?>

  <span class="user-picture">
      <?php
      if ($user_picture):
          print $user_picture; 
      else: ?>
      <a class="active" title="View user profile." href="users/<?php print $user->name; ?>">
          <img title="<?php print $user->name; ?>'s picture" alt='s picture' src="/<?php print path_to_theme() . '/accrualnet-internals/images/avatars/male/Black.png'; ?>"/>
      </a>
      <?php endif; ?>
  </span>

