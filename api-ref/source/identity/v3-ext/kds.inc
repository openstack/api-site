.. -*- rst -*-

================================================
Key Distribution Server (KDS) extension (OS-KDS)
================================================

The Key Distribution Server (KDS) is a trusted third party that
generates and securely distributes signing and encryption keys to
communicating parties. These shared keys enable parties to exchange
authenticated, confidential messages. KDS is an integral part of
the RPC message security implementation. To establish a trusted
relationship between the party and the KDS, a properly authorized
user, such as a cloud administrator, must assign a long-term shared
key to the communicating party. Assigning a key to a party requires
assigning an identity to that party in the KDS. An identity
includes a unique party name and the associated long-term shared
key. This party name is used to identify a party when it
communicates with KDS or another party.

The KDS enables two individual parties or one individual party and
a group party to exchange secure messages. To get keys so that it
can communicate with another party, a party makes an authenticated
request to KDS for a ticket. The KDS returns an encrypted ticket to
the requesting party. The KDS encrypts the ticket with the long-
term shared key that is associated with that party. Only the
associated party or the KDS itself can decrypt the ticket.

The KDS issues a ticket that contains a copy of the shared
encryption and signing keys. These keys are for the source party,
which is the party that requests the ticket. The ticket also
contains a payload that is intended for the destination party,
which is the party with whom the source party wants to communicate.
This payload contains the information that the destination party
can use to derive the shared encryption and signing keys. When the
destination party is:

- An individual. The payload is encrypted with the long-term shared
  key that is associated with the destination party.

- A group. The payload is encrypted with a shared group key that the
  KDS makes available to all members of the group. This encryption
  enables the destination party to trust that the information in
  the payload was supplied by the KDS.

When the source party is ready to communicate with the destination
party, it sends this encrypted payload to the destination party
along with whatever data it has protected with the shared signing
and encryption keys. The destination party can decrypt the payload
and derive the shared encryption and signing keys by using the
payload information. Both parties have a copy of the shared signing
and encryption keys that are trusted as being issued by the KDS.
The destination party uses these shared keys to authenticate and
decrypt the data sent by the source party.

Other guidelines:

- When a source party must send secure messages to multiple
  recipients, an authorized user can define a KDS group for the
  recipients. Membership in a group is determined by comparing a
  party name with the group name. The party is considered a member
  if the party name matches ``< group name > .*``. For example, a
  party named ``scheduler.host.example.com`` is considered a member
  of the ``scheduler`` group. This method is the same method that
  is used to name message queues in OpenStack.

- When a source party requests a ticket for a destination party that
  is a group, KDS generates a short-lived group key and assigns it
  to the group. This group key is used to encrypt the payload in
  the ticket, which contains the information that the destination
  party uses to derive the shared signing and encryption keys.

- When an individual destination party must decrypt the payload that
  it receives from the source party as a part of a group message,
  it makes an authenticated request to KDS to get the short-lived
  group key. If the requester is a member of the target group, KDS
  provides the short-lived group key encrypted with the long-term
  shared key associated with the individual destination party. The
  individual destination party can then decrypt the group key,
  which enables it to decrypt the payload and derive the shared
  signing and encryption keys to use to authenticate and decrypt
  the data sent by the source party.

- When a sender gets keys to send a message to a group, all group
  members and the sender share the signing and encryption keys,
  which makes it impossible for an individual destination party to
  determine whether a message was sent by the source party or by
  another destination party who is a group member. The destination
  party can confirm only that the message was sent by a party who
  has the shared signing and encryption keys. When a sender uses
  keys to send a message to a group, all group members must trust
  other members to operate in good faith.

The signing and encryption keys that communicating parties share
are short-lived. The life span of these keys is defined by a
validity period that is set by the KDS when it issues the ticket. A
suggested reasonable default validity period is 15 minutes, though
the implementation determines the appropriate validity period.

After the validity period for the keys expires, a party should
refuse to use those keys to prevent the use of compromised keys.
This requires the source party to request a new ticket from the KDS
to get a new set of keys. An implementation can implement a grace
period to account for clock skew between parties. This grace period
enables a destination party to accept messages that use recently
expired keys. If you use a grace period, its duration should be
five or fewer minutes.

A key server, unlike a pure public key-based system, can regulate
the encryption and signing key exchange. When keys are requested,
the key server actively distributes keys to communicating parties,
applies access control, and denies communication between arbitrary
peers in the system. This enables centralized access control,
prevents unauthorized communication, and eliminates the need to
perform post-authentication access control and policy lookups on
the receiving side.

The KDS requires that all ticket requests are authenticated and,
where appropriate, data is encrypted. You must pass any time stamp
value to the API as a `UTC
<https://en.wikipedia.org/wiki/ISO_8601#UTC>`_ `ISO 8601
<https://en.wikipedia.org/wiki/ISO_8601>`_ date and time string
that includes microseconds. For example,
``2012-03-26T10:01:01.720000``.

The default algorithms for message authentication and encryption
are, respectively, HMAC-SHA-256 and AES-128-CBC. Therefore, the
default block size is 128 bit.

The source party that requests a ticket must send the encrypted
``esek`` payload to the destination party. The source and
destination strings used when requesting the ticket also must be
sent to the destination party to enable it to derive the shared
signing end encryption keys. The messaging implementation is
responsible for transferring this data to the destination party.

The key derivation used to generate the shared signing and
encryption keys uses the Hashed Message Authentication Code
(HMAC)-based key derivation function (HKDF) standard, as described
in RFC 5869. The destination party must use the HKDF ``expand``
function by using the information that it receives from the source
party to complete derivation of the shared signing and encryption
keys. The inputs to the HKDF ``expand`` function are:

::

   HKDF-Expand(esek.key, info, 256)

The ``info`` input for the HKDF ``expand`` function is a string
that concatenates the source, destination, and ``esek.timestamp``
strings by using a comma (``,``) separator between each element.
The following example shows a valid ``info`` string where
``scheduler.host.example.com`` is the source,
``compute.host.example.com`` is the destination, and
``2012-03-26T10:01:01.720000`` is the ``esek.timestamp``:

::

   scheduler.host.example.com,compute.host.example.com,2012-03-26T10:01:01.720000

The output of the HKDF expand function is an array of bytes of 256
bit length. The first half is the signing key, and the second half
is the encryption key.

Create and delete requests for long-term keys are restricted to
authorized users, such as cloud administrators. The authentication
and authorization for these requests is left up to the
implementation, though the implementation should leverage the
Identity API for these purposes.


Create group
============

.. rest_method::  POST /v3/groups/{name}

Creates a group in the KDS.

Membership in groups is based on the party name. For example, a
``scheduler`` group implicitly includes any party name that starts
with ``scheduler``. For example, a member named
``scheduler.host.example.com``.

Error response codes:201,413,415,405,404,403,401,400,503,409,


Request
-------

.. rest_parameters:: parameters.yaml

   - name: name


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - name: name














Delete group
============

.. rest_method::  DELETE /v3/groups/{name}

Deletes a group from the KDS.

Error response codes:204,413,415,405,404,403,401,400,503,409,


Request
-------

.. rest_parameters:: parameters.yaml

   - name: name















Show group key
==============

.. rest_method::  GET /v3/groups

Shows the key for a group in the KDS.

When a ticket is requested where the destination is a group, a
group key is generated that is valid for a predetermined amount of
time. Any member of the group can get the key as long as it is
still valid. Group keys are necessary to verify signatures and
decrypt messages that have a group name as the target.

Error response codes:201,413,405,404,403,401,400,503,


Request
-------

.. rest_parameters:: parameters.yaml



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - name: name












Generate ticket
===============

.. rest_method::  POST /v3/tickets

Generates a ticket to facilitate messaging between a source and destination.

A generate ticket request contains metadata that you specify as a
Base64-encoded JSON object and a signature.

The response shows the metadata, encrypted ticket, and signature.

Error response codes:201,413,415,405,404,403,401,400,503,409,


Request
-------

.. rest_parameters:: parameters.yaml

   - generation: generation
   - signature: signature
   - metadata: metadata

Request Example
---------------

.. literalinclude:: ../samples/OS-KDS/ticket-generate-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - ticket: ticket
   - signature: signature
   - metadata: metadata














Create key
==========

.. rest_method::  POST /v3/keys/{name}

Creates a long-term key in the KDS.

The request body contains the key.

The response shows the key name and generation value.

Error response codes:201,413,415,405,404,403,401,400,503,409,


Request
-------

.. rest_parameters:: parameters.yaml

   - name: name

Request Example
---------------

.. literalinclude:: ../samples/OS-KDS/key-create-request.json
   :language: javascript



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - generation: generation
   - name: name














Delete key
==========

.. rest_method::  DELETE /v3/keys/{name}

Deletes a long-term key from the KDS.

Error response codes:204,


Request
-------

.. rest_parameters:: parameters.yaml

   - name: name





