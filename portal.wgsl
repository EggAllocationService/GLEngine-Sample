struct RenderUniforms {
    projectionViewMatrix: mat4x4<f32>,
    projectionMatrix: mat4x4<f32>,
    viewMatrix: mat4x4<f32>,
    lightCount: i32,
    time: f32
}
struct ModelData {
    m: mat4x4<f32>
}

@group(0)
@binding(0)
var<uniform> camera: RenderUniforms;

@group(1)
@binding(0)
var starfield: texture_2d<f32>;

@group(1)
@binding(1)
var samp: sampler;

@group(1)
@binding(2)
var noise: texture_2d<f32>;

@group(1)
@binding(3)
var noiseSamp: sampler;

var<immediate> m: ModelData;

struct VertexIn {
    @location(0) pos: vec3f,
    @location(1) normal: vec3f,
    @location(2) uv: vec2f
}

struct VertexOut {
    @builtin(position) pos: vec4f,
    @location(1) normal: vec3f,
    @location(2) uv: vec2f
}

@vertex
fn vs(i: VertexIn) -> VertexOut {
    let MVP = camera.projectionViewMatrix * m.m;
    var result: VertexOut;
    result.pos = MVP * vec4f(i.pos, 1.0);
    result.normal = (m.m * vec4f(i.normal, 1)).xyz;
    result.uv = i.uv;
    return result;
}

fn rotation2D(theta: f32) -> mat3x3f {
    return mat3x3f(cos(theta), sin(theta), 0, -sin(theta), cos(theta), 0, 0, 0, 1);
}

const SCALE_TRANSLATE: mat3x3f = mat3x3f(
    0.5, 0.0, 0.0,
    0.0, 0.5, 0.0,
    1, 1, 1.0,
);

fn portal_layer(layer: f32) -> mat3x3f {
    // wgsl matrix initializers are column-major
    let xOffset = 17.0 / layer;
    let yOffset = (2.0 + layer / 1.5) * (camera.time / 450);
    let translate  = mat3x3f(
                            1.0, 0.0, 0.0,
                            0.0, 1.0, 0.0,
                            xOffset, yOffset, 1.0
                        );
    let rotate = rotation2D(radians((layer * layer * 4321.0 + layer * 9.0) * 2.0));
    let scale = mat3x3f(
        (4.5 - layer / 4.0) * 2.0, 0.0, 0.0,
        0.0, (4.5 - layer / 4.0) * 2.0, 0.0,
        0.0, 0.0, 1.0
    );

    return translate * rotate * scale * SCALE_TRANSLATE;
}

const COLORS = array(
    vec3f(0.022087, 0.098399, 0.110818),
    vec3f(0.011892, 0.095924, 0.089485),
    vec3f(0.027636, 0.101689, 0.100326),
    vec3f(0.046564, 0.109883, 0.114838),
    vec3f(0.064901, 0.117696, 0.097189),
    vec3f(0.063761, 0.086895, 0.123646),
    vec3f(0.084817, 0.111994, 0.166380),
    vec3f(0.097489, 0.154120, 0.091064),
    vec3f(0.106152, 0.131144, 0.195191),
    vec3f(0.097721, 0.110188, 0.187229),
    vec3f(0.133516, 0.138278, 0.148582),
    vec3f(0.070006, 0.243332, 0.235792),
    vec3f(0.196766, 0.142899, 0.214696),
    vec3f(0.047281, 0.315338, 0.321970),
    vec3f(0.204675, 0.390010, 0.302066),
    vec3f(0.080955, 0.314821, 0.661491)
);

@fragment
fn fs(i: VertexOut) -> @location(0) vec4f {
    var color = textureSample(noise, noiseSamp, i.uv).xyz * COLORS[0] * 0.1;

    for (var j:u32 = 0; j < 14; j++) {
        let transform = portal_layer(f32(j + 1));
        let coords = transform * vec3f(i.uv, 1);
        let uv = coords.xy / coords.z;
        let intensity = textureSample(starfield, samp, uv).xyz;
        color += intensity * COLORS[j];
    }
    return vec4f(color, 1.0);
}

