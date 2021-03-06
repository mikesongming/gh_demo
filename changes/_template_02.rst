{% set package = versiondata.name|lower %}
.. _Unreleased: https://foss.heptapod.net/fluiddyn/{{ package }}/-/compare/{{ versiondata.version }}...branch%2Fdefault

{% set underline = underlines[0] -%}
{% set version_heading = "v{} ({})".format(versiondata.version, versiondata.date) -%}
{{ version_heading }}
{{ underline * version_heading|length }}
{% set underline = underlines[1] -%}
{% for section, _ in sections.items() -%}{# section loop #}
{% if sections[section] -%}{# section #}
{% for category, val in definitions.items() if category in sections[section] %}{# category loop #}

{{ definitions[category]['name'] }}
{{ underline * definitions[category]['name']|length }}
{% if definitions[category]['showcontent'] -%}{# category #}
{% for text, values in sections[section][category].items() %}{# fragments loop #}
* {{values|join(', ') }} : {{ text }}
{% endfor %}{# fragments loop #}
{% else %}{# fragments #}
* {{ sections[section][category]['']|join(', ') }}
{% endif -%}{# fragments #}
{% if sections[section][category]|length == 0 %}{# category null #}
No significant changes.
{% else -%}{# category null #}
{% endif -%}{# category null #}
{% endfor -%}{# category loop #}
{% else -%}{# section #}
No significant changes.

{% endif %}{# section null #}
{% endfor %}{# section loop #}

.. v{{ versiondata.version }}: https://foss.heptapod.net/fluiddyn/{{ package }}/-/compare/x.y.z...{{ versiondata.version }}
.. FIXME: replace x.y.z with previous version in the above line and remove old `_Unreleased` link below
