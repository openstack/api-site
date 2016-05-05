.. -*- rst -*-

==============================
Tasks (since API v2.2) (tasks)
==============================

Creates, lists, and shows details for tasks.


List tasks
==========

.. rest_method::  GET /v2/tasks

Lists tasks.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - sort_dir: sort_dir
   - sort_key: sort_key
   - type: type
   - status: status


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - tasks: tasks
   - type: type
   - id: id



Response Example
----------------

.. literalinclude:: ../samples/tasks-list-response.json
   :language: javascript




Create task
===========

.. rest_method::  POST /v2/tasks

Creates a task.

Error response codes:201,


Request
-------

.. rest_parameters:: parameters.yaml


Request Example
---------------

.. literalinclude:: ../samples/task-create-request.json
   :language: javascript







Show task details
=================

.. rest_method::  GET /v2/tasks/{task_id}

Shows details for a task.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - task_id: task_id


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - status: status
   - type: type
   - id: id



Response Example
----------------

.. literalinclude:: ../samples/task-show-response.json
   :language: javascript



