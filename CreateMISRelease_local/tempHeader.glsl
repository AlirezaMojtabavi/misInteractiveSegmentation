#version 130
#define GLSL_VERSION_130
precision highp float;
#define VRN_TEXTURE_2D
#define VRN_GLEW_ARB_draw_buffers
//$ @name = "outport0"
out vec4 FragData0;
#define VRN_TEXTURE_3D
#define RC_CALC_GRADIENTS(voxel, samplePos, volume, volumeParameters, t, rayDirection, entryPoints, entryParameters) calcGradientR(volume, volumeParameters, samplePos, t, rayDirection, entryPoints, entryParameters);
#define RC_APPLY_SHADING(gradient, samplePos, volumeParameters, ka, kd, ks) phongShading(gradient, samplePos, volumeParameters, ka, kd, ks);
#define RC_APPLY_COMPOSITING(result, color, samplePos, gradient, t, tDepth) compositeDVR(result, color, t, tDepth);
