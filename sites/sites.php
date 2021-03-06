<?php

/**
 * @file
 * Configuration file for Drupal's multi-site directory aliasing feature.
 *
 * Drupal searches for an appropriate configuration directory based on the
 * website's hostname and pathname. A detailed description of the rules for
 * discovering the configuration directory can be found in the comment
 * documentation in 'sites/default/default.settings.php'.
 *
 * This file allows you to define a set of aliases that map hostnames and
 * pathnames to configuration directories. These aliases are loaded prior to
 * scanning for directories, and they are exempt from the normal discovery
 * rules. The aliases are defined in an associative array named $sites, which
 * should look similar to the following:
 *
 * $sites = array(
 *   'devexample.com' => 'example.com',
 *   'localhost.example' => 'example.com',
 * );
 *
 * The above array will cause Drupal to look for a directory named
 * "example.com" in the sites directory whenever a request comes from
 * "example.com", "devexample.com", or "localhost/example". That is useful
 * on development servers, where the domain name may not be the same as the
 * domain of the live server. Since Drupal stores file paths into the database
 * (files, system table, etc.) this will ensure the paths are correct while
 * accessed on development servers.
 *
 * To use this file, copy and rename it such that its path plus filename is
 * 'sites/sites.php'. If you don't need to use multi-site directory aliasing,
 * then you can safely ignore this file, and Drupal will ignore it too.
 */

/**
 * DO NOT EDIT THIS FILE ON AN INDVIDUAL SITE!
 *
 * We should have a master copy of this file in version control.  If
 * there is an error in the file, for example because the name or alias
 * of a server has changed:
 *
 *   Checkout the master copy from oce_dev/Products/Drupal/sites/sites.php
 *   Make the required change.
 *   Test it.
 *   Check it in.
 *   Copy it to all servers.
 *
 * The reason for this procedure is that a file system may be copied
 * from one server to another, for example to install drupal updates or
 * to restore files on one server based on those in another.  It is
 * therefore important that all mappings in this file work properly on
 * all sites.
 */

$sites = array(
  // AccrualNet
  'accrualnet-dev-sg.cancer.gov'  => 'accrualnet.cancer.gov',
  'accrualnet-qa-sg.cancer.gov'   => 'accrualnet.cancer.gov',
  'accrualnet-stage-sg.cancer.gov' => 'accrualnet.cancer.gov',
  'accrualnet.cancer.gov'      => 'accrualnet.cancer.gov',

);
