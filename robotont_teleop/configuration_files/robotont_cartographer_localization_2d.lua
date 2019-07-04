include "robotont_cartographer_2d.lua"

--TRAJECTORY_BUILDER.pure_localization = true

POSE_GRAPH.optimize_every_n_nodes = 10
POSE_GRAPH.matcher_translation_weight = 1e5
POSE_GRAPH.matcher_rotation_weight = 0.01
POSE_GRAPH.constraint_builder.min_score = 0.65
POSE_GRAPH.constraint_builder.global_localization_min_score = 0.7

return options
